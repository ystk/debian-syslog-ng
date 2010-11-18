/*
 * Copyright (c) 2002-2009 BalaBit IT Ltd, Budapest, Hungary
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * Note that this permission is granted for only version 2 of the GPL.
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
  
#include "syslog-ng.h"
#include "cfg.h"
#include "messages.h"
#include "memtrace.h"
#include "children.h"
#include "misc.h"
#include "stats.h"
#include "apphook.h"
#include "alarms.h"
#include "logqueue.h"
#include "gprocess.h"
#include "control.h"
#include "timeutils.h"

#if ENABLE_SSL
#include <openssl/ssl.h>
#include <openssl/rand.h>
#endif


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <grp.h>

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

static gchar *cfgfilename = PATH_SYSLOG_NG_CONF;
static gchar *install_dat_filename = PATH_INSTALL_DAT;
static gchar *installer_version = NULL;
static const gchar *persist_file = PATH_PERSIST_CONFIG;
static gboolean syntax_only = FALSE;
static gboolean seed_rng = FALSE;
static gboolean display_version = FALSE;
static gchar *ctlfilename = PATH_CONTROL_SOCKET;

static volatile sig_atomic_t sig_hup_received = FALSE;
static volatile sig_atomic_t sig_term_received = FALSE;
static volatile sig_atomic_t sig_child_received = FALSE;

static void 
sig_hup_handler(int signo)
{
  sig_hup_received = TRUE;
}

static void
sig_term_handler(int signo)
{
  sig_term_received = TRUE;
}

static void
sig_child_handler(int signo)
{
  sig_child_received = TRUE;
}

static void
setup_signals(void)
{
  struct sigaction sa;
  
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &sa, NULL);
  sa.sa_handler = sig_hup_handler;
  sigaction(SIGHUP, &sa, NULL);
  sa.sa_handler = sig_term_handler;
  sigaction(SIGTERM, &sa, NULL);
  sa.sa_handler = sig_term_handler;
  sigaction(SIGINT, &sa, NULL);
  sa.sa_handler = sig_child_handler;
  sigaction(SIGCHLD, &sa, NULL);
}

gboolean
stats_timer(gpointer st)
{
  stats_generate_log();
  return TRUE;
}

static GStaticMutex main_loop_lock = G_STATIC_MUTEX_INIT;
static GMainLoop *main_loop = NULL;
static GPollFunc system_poll_func = NULL;

void
main_loop_wakeup(void)
{
  g_static_mutex_lock(&main_loop_lock);
  if (main_loop)
    g_main_context_wakeup(g_main_loop_get_context(main_loop));
  g_static_mutex_unlock(&main_loop_lock);
}

gint
main_context_poll(GPollFD *ufds, guint nfsd, gint timeout_)
{
  gint ret = (*system_poll_func)(ufds, nfsd, timeout_);
  update_g_current_time();
  return ret;
}

int 
main_loop_run(GlobalConfig **cfg)
{
  gint iters;
  guint stats_timer_id = 0;
  sigset_t ss;

  msg_notice("syslog-ng starting up", 
             evt_tag_str("version", VERSION),
             NULL);
  main_loop = g_main_loop_new(NULL, TRUE);
  if ((*cfg)->stats_freq > 0)
    stats_timer_id = g_timeout_add((*cfg)->stats_freq * 1000, stats_timer, NULL);
    
  control_init(ctlfilename, g_main_loop_get_context(main_loop));

  system_poll_func = g_main_context_get_poll_func(g_main_loop_get_context(main_loop));
  g_main_context_set_poll_func(g_main_loop_get_context(main_loop), main_context_poll);
  while (g_main_loop_is_running(main_loop))
    {
      if ((*cfg)->time_sleep > 0)
        {
          struct timespec ts;
          
          ts.tv_sec = (*cfg)->time_sleep / 1000;
          ts.tv_nsec = ((*cfg)->time_sleep % 1000) * 1E6;
          
          nanosleep(&ts, NULL);
        }
      g_main_context_iteration(g_main_loop_get_context(main_loop), TRUE);
      if (sig_hup_received)
        {
          sigemptyset(&ss);
          sigaddset(&ss, SIGHUP);
          sigprocmask(SIG_BLOCK, &ss, NULL);
          sig_hup_received = FALSE;

          /* this may handle multiple SIGHUP signals, however it doesn't
           * really matter if we received only a single or multiple SIGHUPs
           * until we make sure that we handle the last one.  Since we
           * blocked the SIGHUP signal and reset sig_hup_received to FALSE,
           * we can be sure that if we receive an additional SIGHUP during
           * signal processing we get the new one when we finished this, and
           * handle that one as well. */

	  app_pre_config_loaded();
          (*cfg) = cfg_reload_config(cfgfilename, (*cfg));
	  app_post_config_loaded();
          msg_notice("Configuration reload request received, reloading configuration", 
                       NULL);
          reset_cached_hostname();
          if ((*cfg)->stats_freq > 0)
            {
              if (stats_timer_id != 0)
                g_source_remove(stats_timer_id);
              stats_timer_id = g_timeout_add((*cfg)->stats_freq * 1000, stats_timer, NULL);
            }
          stats_cleanup_orphans();
          sigprocmask(SIG_UNBLOCK, &ss, NULL);
        }
      if (sig_term_received)
        {
          msg_info("Termination requested via signal, terminating", NULL);
          sig_term_received = FALSE;
          break;
        }
      if (sig_child_received)
	{
	  pid_t pid;
	  int status;

          sigemptyset(&ss);
          sigaddset(&ss, SIGCHLD);
          sigprocmask(SIG_BLOCK, &ss, NULL);
	  sig_child_received = FALSE;

	  /* this may handle multiple SIGCHLD signals, however it doesn't
	   * matter if one or multiple SIGCHLD was received assuming that
	   * all exited child process are waited for */

          do
	    {
	      pid = waitpid(-1, &status, WNOHANG);
	      child_manager_sigchild(pid, status);
	    }
          while (pid > 0);
          sigprocmask(SIG_UNBLOCK, &ss, NULL);
	}
    }
  control_destroy();
  msg_notice("syslog-ng shutting down", 
             evt_tag_str("version", VERSION),
             NULL);
  iters = 0;
  while (g_main_context_iteration(NULL, FALSE) && iters < 3)
    {
      iters++;
    }
  g_static_mutex_lock(&main_loop_lock);
  g_main_loop_unref(main_loop);
  main_loop = NULL;
  g_static_mutex_unlock(&main_loop_lock);
  return 0;
}

#if ENABLE_SSL
static void
tls_init(void)
{
  char rnd_file[256];
  
  if (seed_rng)
    {
      RAND_file_name(rnd_file, sizeof(rnd_file));
      if (rnd_file[0])
        RAND_load_file(rnd_file, -1);
    }
  SSL_library_init();
  SSL_load_error_strings();
  SSLeay_add_all_algorithms();
}

static void
tls_deinit(void)
{
  char rnd_file[256];
  
  if (seed_rng)
    {
      RAND_file_name(rnd_file, sizeof(rnd_file));
      if (rnd_file[0])
        RAND_write_file(rnd_file);
    }
}
#else

#define tls_init()
#define tls_deinit()

#endif

#ifdef YYDEBUG
extern int yydebug;
#endif


static GOptionEntry syslogng_options[] = 
{
  { "cfgfile",           'f',         0, G_OPTION_ARG_STRING, &cfgfilename, "Set config file name, default=" PATH_SYSLOG_NG_CONF, "<config>" },
  { "persist-file",      'R',         0, G_OPTION_ARG_STRING, &persist_file, "Set the name of the persistent configuration file, default=" PATH_PERSIST_CONFIG, "<fname>" },
  { "syntax-only",       's',         0, G_OPTION_ARG_NONE, &syntax_only, "Only read and parse config file", NULL},
  { "version",           'V',         0, G_OPTION_ARG_NONE, &display_version, "Display version number (" PACKAGE " " VERSION ")", NULL },
  { "seed",              'S',         0, G_OPTION_ARG_NONE, &seed_rng, "Seed the RNG using ~/.rnd or $RANDFILE", NULL},
  { "control",           'c',         0, G_OPTION_ARG_STRING, &ctlfilename, "Set syslog-ng control socket, default=" PATH_CONTROL_SOCKET, "<ctlpath>" },
#ifdef YYDEBUG
  { "yydebug",           'y',         0, G_OPTION_ARG_NONE, &yydebug, "Enable configuration parser debugging", NULL },
#endif
  { NULL },
};

/* 
 * Returns: exit code to be returned to the calling process.
 */
int 
initial_init(GlobalConfig **cfg)
{
  
  app_startup();
  setup_signals();

  tls_init();
  *cfg = cfg_new(cfgfilename);
  if (!(*cfg))
    {
      return 1;
    }

  if (syntax_only)
    {
      return 0;
    }

  cfg_persist_config_load(*cfg, persist_file);

  if (!cfg_init(*cfg))
    {
      return 2;
    }
  return 0;
}

#define INSTALL_DAT_INSTALLER_VERSION "INSTALLER_VERSION"

gboolean
get_installer_version(gchar **inst_version)
{
  gchar line[1024];
  gboolean result = FALSE;
  FILE *f_install = fopen(install_dat_filename, "r");

  if (!f_install)
    return FALSE;

  while (fgets(line, sizeof(line), f_install) != NULL)
    {
      if (strncmp(line, INSTALL_DAT_INSTALLER_VERSION, strlen(INSTALL_DAT_INSTALLER_VERSION)) == 0)
        {
          gchar *pos = strchr(line, '=');
          if (pos)
            {
              *inst_version = strdup(pos+1);
              result = TRUE;
              break;
            }
        }
    }
  fclose(f_install);
  return result;
}

#define ON_OFF_STR(x) (x ? "on" : "off")


void
version(void)
{
  if (!get_installer_version(&installer_version) || installer_version==NULL)
    {
      installer_version=VERSION;
    }
  printf(PACKAGE " " VERSION "\n"
         "Installer-Version: %s\n"
         "Revision: " SOURCE_REVISION "\n"
         "Compile-Date: " __DATE__ " " __TIME__ "\n"
         "Enable-Threads: %s\n"
         "Enable-Debug: %s\n"
         "Enable-GProf: %s\n"
         "Enable-Memtrace: %s\n"
         "Enable-Sun-STREAMS: %s\n"
         "Enable-Sun-Door: %s\n"
         "Enable-IPv6: %s\n"
         "Enable-Spoof-Source: %s\n"
         "Enable-TCP-Wrapper: %s\n"
         "Enable-SSL: %s\n"
         "Enable-SQL: %s\n"
         "Enable-Linux-Caps: %s\n"
         "Enable-Pcre: %s\n",
         installer_version,
         ON_OFF_STR(ENABLE_THREADS),
         ON_OFF_STR(ENABLE_DEBUG),
         ON_OFF_STR(ENABLE_GPROF),
         ON_OFF_STR(ENABLE_MEMTRACE),
         ON_OFF_STR(ENABLE_SUN_STREAMS),
         ON_OFF_STR(ENABLE_SUN_DOOR),
         ON_OFF_STR(ENABLE_IPV6),
         ON_OFF_STR(ENABLE_SPOOF_SOURCE),
         ON_OFF_STR(ENABLE_TCP_WRAPPER),
         ON_OFF_STR(ENABLE_SSL),
         ON_OFF_STR(ENABLE_SQL),
         ON_OFF_STR(ENABLE_LINUX_CAPS),
         ON_OFF_STR(ENABLE_PCRE));
}

int 
main(int argc, char *argv[])
{
  GlobalConfig *cfg;
  gint rc;
  GOptionContext *ctx;
  GError *error = NULL;

  z_mem_trace_init("syslog-ng.trace");

  g_process_set_argv_space(argc, (gchar **) argv);
  
  /* NOTE: polling /proc/kmsg requires cap_sys_admin, otherwise it'll always
   * indicate readability. Enabling/disabling cap_sys_admin on every poll
   * invocation seems to be too expensive. So I enable it for now. */
  
  g_process_set_caps("cap_net_bind_service,cap_net_broadcast,cap_net_raw,"
                     "cap_dac_read_search,cap_dac_override,cap_chown,cap_fowner=p "
                     "cap_sys_admin=ep");
  ctx = g_option_context_new("syslog-ng");
  g_process_add_option_group(ctx);
  msg_add_option_group(ctx);
  g_option_context_add_main_entries(ctx, syslogng_options, NULL);
  if (!g_option_context_parse(ctx, &argc, &argv, &error))
    {
      fprintf(stderr, "Error parsing command line arguments: %s", error ? error->message : "Invalid arguments");
      g_option_context_free(ctx);
      return 1;
    }
  g_option_context_free(ctx);
  if (argc > 1)
    {
      fprintf(stderr, "Excess number of arguments\n");
      return 1;
    }

  if (display_version)
    {
      version();
      return 0;
    }

  if (debug_flag)
    {
      log_stderr = TRUE;
    }

  if (syntax_only || debug_flag)
    {
      g_process_set_mode(G_PM_FOREGROUND);
    }

  g_process_set_name("syslog-ng");
  
  /* in this case we switch users early while retaining a limited set of
   * credentials in order to initialize/reinitialize the configuration.
   */
  g_process_start();
  rc = initial_init(&cfg);
  
  if (rc)
    {
      g_process_startup_failed(rc, TRUE);
      return rc;
    }
  else
    {
      if (syntax_only)
        g_process_startup_failed(0, TRUE);
      else
        g_process_startup_ok();
    }

  /* we are running as a non-root user from this point */
  
  app_post_daemonized();
  app_post_config_loaded();
  /* from now on internal messages are written to the system log as well */
  msg_syslog_started();
  
  rc = main_loop_run(&cfg);

  cfg_deinit(cfg);
  
  if (cfg->persist)
    {
      cfg_persist_config_save(cfg, persist_file);
    }

  cfg_free(cfg);
  
  app_shutdown();
  tls_deinit();
  z_mem_trace_dump();
  g_process_finish();
  return rc;
}

