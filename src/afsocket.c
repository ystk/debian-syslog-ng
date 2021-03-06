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
  
#include "afsocket.h"
#include "messages.h"
#include "driver.h"
#include "misc.h"
#include "logwriter.h"
#if ENABLE_SSL
#include "tlstransport.h"
#endif
#include "gprocess.h"
#include "gsocket.h"
#include "stats.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>

#if ENABLE_TCP_WRAPPER
#include <tcpd.h>
int allow_severity = 0;
int deny_severity = 0;
#endif



typedef struct _AFSocketSourceConnection
{
  LogPipe super;
  struct _AFSocketSourceDriver *owner;
  LogPipe *reader;
  int sock;
  GSockAddr *peer_addr;
} AFSocketSourceConnection;

static void afsocket_sd_close_connection(AFSocketSourceDriver *self, AFSocketSourceConnection *sc);

gboolean
afsocket_setup_socket(gint fd, SocketOptions *sock_options, AFSocketDirection dir)
{
  if (dir & AFSOCKET_DIR_RECV)
    {
      if (sock_options->rcvbuf)
        setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &sock_options->rcvbuf, sizeof(sock_options->rcvbuf));
    }
  if (dir & AFSOCKET_DIR_SEND)
    {
      if (sock_options->sndbuf)
        setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &sock_options->sndbuf, sizeof(sock_options->sndbuf));
      if (sock_options->broadcast)
        setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &sock_options->broadcast, sizeof(sock_options->broadcast));
    }
  setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &sock_options->keepalive, sizeof(sock_options->keepalive));
  return TRUE;
}

static gboolean
afsocket_open_socket(GSockAddr *bind_addr, int stream_or_dgram, int *fd)
{
  gint sock;
  
  if (stream_or_dgram)
    sock = socket(bind_addr->sa.sa_family, SOCK_STREAM, 0);
  else
    sock = socket(bind_addr->sa.sa_family, SOCK_DGRAM, 0);
    
  if (sock != -1)
    {
      cap_t saved_caps;

      g_fd_set_nonblock(sock, TRUE);
      g_fd_set_cloexec(sock, TRUE);
      saved_caps = g_process_cap_save();
      g_process_cap_modify(CAP_NET_BIND_SERVICE, TRUE);
      g_process_cap_modify(CAP_DAC_OVERRIDE, TRUE);
      if (g_bind(sock, bind_addr) != G_IO_STATUS_NORMAL)
        {
          gchar buf[256];
          
          g_process_cap_restore(saved_caps);
          msg_error("Error binding socket",
                    evt_tag_str("addr", g_sockaddr_format(bind_addr, buf, sizeof(buf), GSA_FULL)),
                    evt_tag_errno(EVT_TAG_OSERROR, errno),
                    NULL);
          close(sock);
          return FALSE;
        }
      g_process_cap_restore(saved_caps);
      
      *fd = sock;
      return TRUE;
    }
  else
    {
      msg_error("Error creating socket",
                evt_tag_errno(EVT_TAG_OSERROR, errno),
                NULL);
      return FALSE;
    }
}

static gint
afsocket_sc_stats_source(AFSocketSourceConnection *self)
{
  gint source;

  if ((self->owner->flags & AFSOCKET_SYSLOG_PROTOCOL) == 0)
    {
      switch (self->owner->bind_addr->sa.sa_family)
        {
        case AF_UNIX:
          source = !!(self->owner->flags & AFSOCKET_STREAM) ? SCS_UNIX_STREAM : SCS_UNIX_DGRAM;
          break;
        case AF_INET:
          source = !!(self->owner->flags & AFSOCKET_STREAM) ? SCS_TCP : SCS_UDP;
          break;
#if ENABLE_IPV6
        case AF_INET6:
          source = !!(self->owner->flags & AFSOCKET_STREAM) ? SCS_TCP6 : SCS_UDP6;
          break;    
#endif
        default:
          g_assert_not_reached();
          break;
        }
    }
  else
    {
      source = SCS_SYSLOG;
    }
  return source;
}

static gchar *
afsocket_sc_stats_instance(AFSocketSourceConnection *self)
{
  static gchar buf[256];
  
  if (!self->peer_addr)
    {
      return NULL;
    }
  if ((self->owner->flags & AFSOCKET_SYSLOG_PROTOCOL) == 0)
    {
      g_sockaddr_format(self->peer_addr, buf, sizeof(buf), GSA_ADDRESS_ONLY);
    }
  else
    {
      gchar peer_addr[MAX_SOCKADDR_STRING];
  
      g_sockaddr_format(self->peer_addr, peer_addr, sizeof(peer_addr), GSA_ADDRESS_ONLY);
      g_snprintf(buf, sizeof(buf), "%s,%s", self->owner->transport, peer_addr);
    }
  return buf;
}


static gboolean
afsocket_sc_init(LogPipe *s)
{
  AFSocketSourceConnection *self = (AFSocketSourceConnection *) s;
  gint read_flags;
  LogTransport *transport;
  LogProto *proto;

  read_flags = ((self->owner->flags & AFSOCKET_DGRAM) ? LTF_RECV : 0);

#if ENABLE_SSL
  if (self->owner->tls_context)
    {
      TLSSession *tls_session = tls_context_setup_session(self->owner->tls_context);
      
      if (!tls_session)
        return FALSE;
      transport = log_transport_tls_new(tls_session, self->sock, read_flags);
    }
  else
#endif

  transport = log_transport_plain_new(self->sock, read_flags);

  if ((self->owner->flags & AFSOCKET_SYSLOG_PROTOCOL) == 0)
    {
      /* plain protocol */
      proto = log_proto_plain_new_server(transport, self->owner->reader_options.padding,
                   self->owner->reader_options.msg_size,
                   (self->owner->flags & AFSOCKET_DGRAM) ? (LPPF_PKTTERM + LPPF_IGNORE_EOF) : 0);
    }
  else
    {
      if (self->owner->flags & AFSOCKET_DGRAM)
        {
          /* plain protocol */
          proto = log_proto_plain_new_server(transport, self->owner->reader_options.padding,
                       self->owner->reader_options.msg_size,
                      (self->owner->flags & AFSOCKET_DGRAM) ? (LPPF_PKTTERM + LPPF_IGNORE_EOF) : 0);
        }
      else
        {
          /* framed protocol */
          proto = log_proto_framed_new_server(transport, self->owner->reader_options.msg_size);
        }
    }

  self->reader = log_reader_new(proto,
                                ((self->owner->flags & AFSOCKET_LOCAL) ? LR_LOCAL : 0) |
                                ((self->owner->flags & AFSOCKET_SYSLOG_PROTOCOL) ? LR_SYSLOG_PROTOCOL : 0));
  log_reader_set_options(self->reader, s, &self->owner->reader_options, 1, afsocket_sc_stats_source(self), self->owner->super.id, afsocket_sc_stats_instance(self));
  log_reader_set_peer_addr(self->reader, self->peer_addr);
  log_pipe_append(self->reader, s);
  if (log_pipe_init(self->reader, NULL))
    {
      self->owner->connections = g_list_prepend(self->owner->connections, self);
      return TRUE;
    }
  else
    {
      log_pipe_unref(self->reader);
      self->reader = NULL;
    }
  return FALSE;
}

static gboolean
afsocket_sc_deinit(LogPipe *s)
{
  AFSocketSourceConnection *self = (AFSocketSourceConnection *) s;

  self->owner->connections = g_list_remove(self->owner->connections, self);
  log_pipe_unref(&self->owner->super.super);
  self->owner = NULL;
  
  log_pipe_deinit(self->reader);
  log_pipe_unref(self->reader);
  self->reader = NULL;
  return TRUE;
}

static void
afsocket_sc_notify(LogPipe *s, LogPipe *sender, gint notify_code, gpointer user_data)
{
  AFSocketSourceConnection *self = (AFSocketSourceConnection *) s;

  switch (notify_code)
    {
    case NC_CLOSE:
    case NC_READ_ERROR:
      {
        if (self->owner->flags & AFSOCKET_STREAM)
          afsocket_sd_close_connection(self->owner, self);
        break;
      }
    }
}

static void
afsocket_sc_set_owner(AFSocketSourceConnection *self, AFSocketSourceDriver *owner)
{
  if (self->reader)
    log_reader_set_options(self->reader, &self->super, &owner->reader_options, 1, afsocket_sc_stats_source(self), owner->super.id, afsocket_sc_stats_instance(self));
  log_drv_unref(&self->owner->super);
  log_drv_ref(&owner->super);
  self->owner = owner;
  
  log_pipe_append(&self->super, &owner->super.super);

}

static void 
afsocket_sc_free(LogPipe *s)
{
  AFSocketSourceConnection *self = (AFSocketSourceConnection *) s;
  
  g_assert(!self->reader);
  g_sockaddr_unref(self->peer_addr);
  log_pipe_free(s);
}

AFSocketSourceConnection *
afsocket_sc_new(AFSocketSourceDriver *owner, GSockAddr *peer_addr, int fd)
{
  AFSocketSourceConnection *self = g_new0(AFSocketSourceConnection, 1);

  log_pipe_init_instance(&self->super);  
  self->super.init = afsocket_sc_init;
  self->super.deinit = afsocket_sc_deinit;
  self->super.notify = afsocket_sc_notify;
  self->super.free_fn = afsocket_sc_free;
  log_drv_ref(&owner->super);
  self->owner = owner;


  self->peer_addr = g_sockaddr_ref(peer_addr);  
  self->sock = fd;
  return self;
}

void 
afsocket_sd_set_keep_alive(LogDriver *s, gint enable)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  
  if (enable)
    self->flags |= AFSOCKET_KEEP_ALIVE;
  else
    self->flags &= ~AFSOCKET_KEEP_ALIVE;
}

void 
afsocket_sd_set_max_connections(LogDriver *s, gint max_connections)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  
  self->max_connections = max_connections;
}

#if ENABLE_SSL
void
afsocket_sd_set_tls_context(LogDriver *s, TLSContext *tls_context)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  
  self->tls_context = tls_context;
}
#endif

static inline gchar *
afsocket_sd_format_persist_name(AFSocketSourceDriver *self, gboolean listener_name)
{
  static gchar persist_name[128];
  gchar buf[64];
  
  g_snprintf(persist_name, sizeof(persist_name),
             listener_name ? "afsocket_sd_listen_fd(%s,%s)" : "afsocket_sd_connections(%s,%s)",
             !!(self->flags & AFSOCKET_STREAM) ? "stream" : "dgram",
             g_sockaddr_format(self->bind_addr, buf, sizeof(buf), GSA_FULL));
  return persist_name;
}

gboolean 
afsocket_sd_process_connection(AFSocketSourceDriver *self, GSockAddr *client_addr, GSockAddr *local_addr, gint fd)
{
  gchar buf[MAX_SOCKADDR_STRING], buf2[MAX_SOCKADDR_STRING];
#if ENABLE_TCP_WRAPPER
  if (client_addr && (client_addr->sa.sa_family == AF_INET
#if ENABLE_IPV6
                   || client_addr->sa.sa_family == AF_INET6
#endif
     ))
    {
      struct request_info req;
   
      request_init(&req, RQ_DAEMON, "syslog-ng", RQ_FILE, fd, 0);
      fromhost(&req);
      if (hosts_access(&req) == 0)
        {
          
          msg_error("Syslog connection rejected by tcpd",
                    evt_tag_str("client", g_sockaddr_format(client_addr, buf, sizeof(buf), GSA_FULL)),
                    evt_tag_str("local", g_sockaddr_format(local_addr, buf2, sizeof(buf2), GSA_FULL)),
                    NULL);
          return FALSE;
        }
    }
  
#endif

  if (self->num_connections >= self->max_connections)
    {
      msg_error("Number of allowed concurrent connections reached, rejecting connection",
                evt_tag_str("client", g_sockaddr_format(client_addr, buf, sizeof(buf), GSA_FULL)),
                evt_tag_str("local", g_sockaddr_format(local_addr, buf2, sizeof(buf2), GSA_FULL)),
                evt_tag_int("max", self->max_connections),
                NULL);
      return FALSE;
    }
  else
    {
      AFSocketSourceConnection *conn;
      
      conn = afsocket_sc_new(self, client_addr, fd);
      if (log_pipe_init(&conn->super, NULL))
        {
          self->num_connections++;
          log_pipe_append(&conn->super, &self->super.super);
        }
      else
        {
          log_pipe_unref(&conn->super);
          return FALSE;
        }
    }
  return TRUE;
}

#define MAX_ACCEPTS_AT_A_TIME 30

static gboolean
afsocket_sd_accept(gpointer s)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  GSockAddr *peer_addr;
  gchar buf1[256], buf2[256];
  gint new_fd;
  gboolean res;
  int accepts = 0;
  
  while (accepts < MAX_ACCEPTS_AT_A_TIME)
    {
      GIOStatus status;
      
      status = g_accept(self->fd, &new_fd, &peer_addr);
      if (status == G_IO_STATUS_AGAIN)
        {
          /* no more connections to accept */
          break;
        }
      else if (status != G_IO_STATUS_NORMAL)
        {
          msg_error("Error accepting new connection",
                    evt_tag_errno(EVT_TAG_OSERROR, errno),
                    NULL);
          return TRUE;
        }
      if (self->setup_socket && !self->setup_socket(self, new_fd))
        {
          close(new_fd);
          return TRUE;
        }
        
      g_fd_set_nonblock(new_fd, TRUE);
      g_fd_set_cloexec(new_fd, TRUE);

      res = afsocket_sd_process_connection(self, peer_addr, self->bind_addr, new_fd);

      if (res)
        {
          if (peer_addr->sa.sa_family != AF_UNIX)
            msg_notice("Syslog connection accepted",
                        evt_tag_int("fd", new_fd),
                        evt_tag_str("client", g_sockaddr_format(peer_addr, buf1, sizeof(buf1), GSA_FULL)),
                        evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf2, sizeof(buf2), GSA_FULL)),
                        NULL);
          else
            msg_verbose("Syslog connection accepted",
                        evt_tag_int("fd", new_fd),
                        evt_tag_str("client", g_sockaddr_format(peer_addr, buf1, sizeof(buf1), GSA_FULL)),
                        evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf2, sizeof(buf2), GSA_FULL)),
                        NULL);
        }
      else
        {
          close(new_fd);
        }

      g_sockaddr_unref(peer_addr);
      accepts++;
    }
  return TRUE;
}

static void
afsocket_sd_close_connection(AFSocketSourceDriver *self, AFSocketSourceConnection *sc)
{
  gchar buf1[MAX_SOCKADDR_STRING], buf2[MAX_SOCKADDR_STRING];
  
  if (sc->peer_addr->sa.sa_family != AF_UNIX)
    msg_notice("Syslog connection closed",
               evt_tag_int("fd", sc->sock),
               evt_tag_str("client", g_sockaddr_format(sc->peer_addr, buf1, sizeof(buf1), GSA_FULL)),
               evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf2, sizeof(buf2), GSA_FULL)),
               NULL);
  else
    msg_verbose("Syslog connection closed",
               evt_tag_int("fd", sc->sock),
               evt_tag_str("client", g_sockaddr_format(sc->peer_addr, buf1, sizeof(buf1), GSA_FULL)),
               evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf2, sizeof(buf2), GSA_FULL)),
               NULL);
  log_pipe_deinit(&sc->super);
  log_pipe_unref(&sc->super);
  self->num_connections--;
}

static void
afsocket_sd_kill_connection(AFSocketSourceConnection *sc)
{
  log_pipe_deinit(&sc->super);
  log_pipe_unref(&sc->super);
}

static void
afsocket_sd_kill_connection_list(GList *list)
{
  GList *l;
  for (l = list; l; l = g_list_next(l))
    afsocket_sd_kill_connection((AFSocketSourceConnection *) l->data);
}

gboolean
afsocket_sd_init(LogPipe *s)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  gint sock;
  gboolean res = FALSE;
  GlobalConfig *cfg = log_pipe_get_config(s);

#if ENABLE_SSL
  if (self->flags & AFSOCKET_REQUIRE_TLS && !self->tls_context)
    {
      msg_error("Transport TLS was specified, but TLS related parameters missing", NULL);
      return FALSE;
    }
#endif

  if (!self->bind_addr)
    {
      msg_error("No bind address set;", NULL);
    }
  log_reader_options_init(&self->reader_options, cfg, self->super.group);
  
  /* fetch persistent connections first */  
  if ((self->flags & AFSOCKET_KEEP_ALIVE))
    {
      GList *p;

      self->connections = cfg_persist_config_fetch(cfg, afsocket_sd_format_persist_name(self, FALSE), NULL, NULL);
      for (p = self->connections; p; p = p->next)
        {
          afsocket_sc_set_owner((AFSocketSourceConnection *) p->data, self);
        }
    }

  /* ok, we have connection list, check if we need to open a listener */
  sock = -1;
  if (self->flags & AFSOCKET_STREAM)
    {
      GSource *source;
      
      if (self->flags & AFSOCKET_KEEP_ALIVE)
        {
          /* NOTE: this assumes that fd 0 will never be used for listening fds,
           * main.c opens fd 0 so this assumption can hold */
          sock = GPOINTER_TO_UINT(cfg_persist_config_fetch(cfg, afsocket_sd_format_persist_name(self, TRUE), NULL, NULL)) - 1;
        }

      if (sock == -1)
        {
          if (!afsocket_open_socket(self->bind_addr, !!(self->flags & AFSOCKET_STREAM), &sock))
            return self->super.optional;
        }
      
      /* set up listening source */
      if (listen(sock, self->listen_backlog) < 0)
        {
          msg_error("Error during listen()",
                    evt_tag_errno(EVT_TAG_OSERROR, errno),
                    NULL);
          close(sock);
          return FALSE;
        }
        
      if (self->setup_socket && !self->setup_socket(self, sock))
        {
          close(sock);
          return FALSE;
        }

      self->fd = sock;
      source = g_listen_source_new(self->fd);
      
      /* the listen_source references us, which is freed when the source is deleted */
      log_pipe_ref(s); 
      g_source_set_callback(source, afsocket_sd_accept, self, (GDestroyNotify) log_pipe_unref);
      self->source_id = g_source_attach(source, NULL);
      g_source_unref(source);
      res = TRUE;
    }
  else
    {
      if (!self->connections)
        {
          if (!afsocket_open_socket(self->bind_addr, !!(self->flags & AFSOCKET_STREAM), &sock))
            return self->super.optional;
        }
      self->fd = -1;

      if (!self->setup_socket(self, sock))
        {
          close(sock);
          return FALSE;
        }
      
      /* we either have self->connections != NULL, or sock contains a new fd */
      if (self->connections || afsocket_sd_process_connection(self, NULL, self->bind_addr, sock))
        res = TRUE;
    }
  return res;
}

static void
afsocket_sd_close_fd(gpointer value)
{
  gint fd = GPOINTER_TO_UINT(value) - 1;
  close(fd);
}

gboolean
afsocket_sd_deinit(LogPipe *s)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  if ((self->flags & AFSOCKET_KEEP_ALIVE) == 0 || !cfg->persist)
    {
      GList *p, *next;

      /* we don't store anything across HUPs */
      for (p = self->connections; p; p = next)
        {
          next = p->next;
          afsocket_sd_kill_connection((AFSocketSourceConnection *) p->data);
        }
        
      /* NOTE: we don't need to free the connection list, when a connection
       * is freed it is removed from the list automatically */
      
    }
  else
    {
      /* for AFSOCKET_STREAM source drivers this is a list, for
       * AFSOCKET_DGRAM this is a single connection */
      
      cfg_persist_config_add(cfg, afsocket_sd_format_persist_name(self, FALSE), self->connections, -1, (GDestroyNotify) afsocket_sd_kill_connection_list, FALSE);
    }
  self->connections = NULL;

  if (self->flags & AFSOCKET_STREAM)
    {
      
      g_source_remove(self->source_id);
      self->source_id = 0;
      if ((self->flags & AFSOCKET_KEEP_ALIVE) == 0)
        {
          msg_verbose("Closing listener fd",
                      evt_tag_int("fd", self->fd),
                      NULL);
          close(self->fd);
        }
      else
        {
          /* NOTE: the fd is incremented by one when added to persistent config
           * as persist config cannot store NULL */

          cfg_persist_config_add(cfg, afsocket_sd_format_persist_name(self, TRUE), GUINT_TO_POINTER(self->fd + 1), -1, afsocket_sd_close_fd, FALSE);
        }
    }
  else if (self->flags & AFSOCKET_DGRAM)
    {
      /* we don't need to close the listening fd here as we have a
       * single connection which will close it */
      
      ;
    }
  
  
  return TRUE;
}

static void
afsocket_sd_notify(LogPipe *s, LogPipe *sender, gint notify_code, gpointer user_data)
{
  switch (notify_code)
    {
    case NC_CLOSE:
    case NC_READ_ERROR:
      {
        g_assert_not_reached();
        break;
      }
    }
}

static gboolean
afsocket_sd_setup_socket(AFSocketSourceDriver *self, gint fd)
{
  return afsocket_setup_socket(fd, self->sock_options_ptr, AFSOCKET_DIR_RECV);
}

void
afsocket_sd_free(LogPipe *s)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  
  log_reader_options_destroy(&self->reader_options);
  g_sockaddr_unref(self->bind_addr);
  self->bind_addr = NULL;
  g_free(self->transport);
   
  log_drv_free(s);
}

void
afsocket_sd_init_instance(AFSocketSourceDriver *self, SocketOptions *sock_options, guint32 flags)
{
  log_drv_init_instance(&self->super);
  
  self->super.super.init = afsocket_sd_init;
  self->super.super.deinit = afsocket_sd_deinit;
  self->super.super.free_fn = afsocket_sd_free;
  self->super.super.queue = log_pipe_forward_msg;
  self->super.super.notify = afsocket_sd_notify;
  self->sock_options_ptr = sock_options;
  self->setup_socket = afsocket_sd_setup_socket;
  self->max_connections = 10;
  self->listen_backlog = 255;
  self->flags = flags | AFSOCKET_KEEP_ALIVE;
  log_reader_options_defaults(&self->reader_options);
}

/* socket destinations */

void afsocket_dd_reconnect(AFSocketDestDriver *self);

#if ENABLE_SSL
void
afsocket_dd_set_tls_context(LogDriver *s, TLSContext *tls_context)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;
  
  self->tls_context = tls_context;
}
#endif

void 
afsocket_dd_set_keep_alive(LogDriver *s, gint enable)
{
  AFSocketSourceDriver *self = (AFSocketSourceDriver *) s;
  
  if (enable)
    self->flags |= AFSOCKET_KEEP_ALIVE;
  else
    self->flags &= ~AFSOCKET_KEEP_ALIVE;
}


static inline gchar *
afsocket_dd_format_persist_name(AFSocketDestDriver *self, const gchar *dest_name, gboolean qfile)
{
  static gchar persist_name[128];
  
  g_snprintf(persist_name, sizeof(persist_name),
             qfile ? "afsocket_dd_qfile(%s,%s)" : "afsocket_dd_connection(%s,%s)",
             !!(self->flags & AFSOCKET_STREAM) ? "stream" : "dgram",
             dest_name);
  return persist_name;
}


static gint
afsocket_dd_stats_source(AFSocketDestDriver *self)
{
  gint source;

  if ((self->flags & AFSOCKET_SYSLOG_PROTOCOL) == 0)
    {
      switch (self->dest_addr->sa.sa_family)
        {
        case AF_UNIX:
          source = !!(self->flags & AFSOCKET_STREAM) ? SCS_UNIX_STREAM : SCS_UNIX_DGRAM;
          break;
        case AF_INET:
          source = !!(self->flags & AFSOCKET_STREAM) ? SCS_TCP : SCS_UDP;
          break;
#if ENABLE_IPV6
        case AF_INET6:
          source = !!(self->flags & AFSOCKET_STREAM) ? SCS_TCP6 : SCS_UDP6;
          break;    
#endif
        }
    }
  else
    {
      source = SCS_SYSLOG;
    }
  return source;
}

static gchar *
afsocket_dd_stats_instance(AFSocketDestDriver *self)
{
  if ((self->flags & AFSOCKET_SYSLOG_PROTOCOL) == 0)
    {
      return self->dest_name;
    }
  else
    {
      static gchar buf[256];

      g_snprintf(buf, sizeof(buf), "%s,%s", self->transport, self->dest_name);
      return buf;
    }
}

static gboolean
afsocket_dd_reconnect_timer(gpointer s)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;
  
  afsocket_dd_reconnect(self);
  return FALSE;
}

#if ENABLE_SSL
static gint
afsocket_dd_tls_verify_callback(gint ok, X509_STORE_CTX *ctx, gpointer user_data)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) user_data;
  
  if (ok && ctx->current_cert == ctx->cert && self->hostname && (self->tls_context->verify_mode & TVM_TRUSTED))
    {
      ok = tls_verify_certificate_name(ctx->cert, self->hostname);
    }

  return ok;
}
#endif

static void
afsocket_dd_start_reconnect_timer(AFSocketDestDriver *self)
{
  if (self->reconnect_timer)
    g_source_remove(self->reconnect_timer);
  self->reconnect_timer = g_timeout_add(self->time_reopen * 1000, afsocket_dd_reconnect_timer, self);
}

gboolean
afsocket_dd_connected(AFSocketDestDriver *self)
{
  gchar buf1[256], buf2[256];
  int error = 0;
  socklen_t errorlen = sizeof(error);
  LogTransport *transport;
  LogProto *proto;
  guint32 transport_flags = 0;

  if (self->flags & AFSOCKET_STREAM)
    {
      transport_flags |= LTF_SHUTDOWN;
      if (getsockopt(self->fd, SOL_SOCKET, SO_ERROR, &error, &errorlen) == -1)
        {
          msg_error("getsockopt(SOL_SOCKET, SO_ERROR) failed for connecting socket",
                    evt_tag_int("fd", self->fd),
                    evt_tag_str("server", g_sockaddr_format(self->dest_addr, buf2, sizeof(buf2), GSA_FULL)),
                    evt_tag_errno(EVT_TAG_OSERROR, errno),
                    evt_tag_int("time_reopen", self->time_reopen),
                    NULL);
          close(self->fd);
          goto error_reconnect;
        }
      if (error)
        {
          msg_error("Syslog connection failed",
                    evt_tag_int("fd", self->fd),
                    evt_tag_str("server", g_sockaddr_format(self->dest_addr, buf2, sizeof(buf2), GSA_FULL)),
                    evt_tag_errno(EVT_TAG_OSERROR, error),
                    evt_tag_int("time_reopen", self->time_reopen),
                    NULL);
          close(self->fd);
          goto error_reconnect;
        }
    }
  msg_notice("Syslog connection established",
              evt_tag_int("fd", self->fd),
              evt_tag_str("server", g_sockaddr_format(self->dest_addr, buf2, sizeof(buf2), GSA_FULL)),
              evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf1, sizeof(buf1), GSA_FULL)),
              NULL);

  if (self->source_id)
    {
      g_source_remove(self->source_id);
      self->source_id = 0;
    }
    
#if ENABLE_SSL
  if (self->tls_context)
    {
      TLSSession *tls_session;
      
      tls_session = tls_context_setup_session(self->tls_context);
      if (!tls_session)
        {
          close(self->fd);
          goto error_reconnect;
        }
        
      tls_session_set_verify(tls_session, afsocket_dd_tls_verify_callback, self, NULL);
      transport = log_transport_tls_new(tls_session, self->fd, transport_flags);
    }
  else
#endif
    transport = log_transport_plain_new(self->fd, transport_flags);

  if (self->flags & AFSOCKET_SYSLOG_PROTOCOL)
    if(self->flags & AFSOCKET_STREAM)
      proto = log_proto_framed_new_client(transport);
    else
      proto = log_proto_plain_new_client(transport);
  else
    proto = log_proto_plain_new_client(transport);

  log_writer_reopen(self->writer, proto);
  return TRUE;
 error_reconnect:
  afsocket_dd_start_reconnect_timer(self);
  return FALSE;
}

gboolean
afsocket_dd_start_connect(AFSocketDestDriver *self)
{
  int sock, rc;
  gchar buf1[MAX_SOCKADDR_STRING], buf2[MAX_SOCKADDR_STRING];

  if (!afsocket_open_socket(self->bind_addr, !!(self->flags & AFSOCKET_STREAM), &sock))
    {
      return FALSE;
    }
    
  if (self->setup_socket && !self->setup_socket(self, sock))
    {
      close(sock);
      return FALSE;
    }
  
  rc = g_connect(sock, self->dest_addr);
  if (rc == G_IO_STATUS_NORMAL)
    {
      self->fd = sock;
      afsocket_dd_connected(self);
    }
  else if (rc == G_IO_STATUS_ERROR && errno == EINPROGRESS)
    {
      GSource *source;

      /* we must wait until connect succeeds */

      self->fd = sock;
      source = g_connect_source_new(sock);
      
      /* a reference is added on behalf of the source, it will be unrefed when
       * the source is destroyed */
      log_pipe_ref(&self->super.super);
      g_source_set_callback(source, (GSourceFunc) afsocket_dd_connected, self, (GDestroyNotify) log_pipe_unref);
      self->source_id = g_source_attach(source, NULL);
      g_source_unref(source);
    }
  else 
    {
      /* error establishing connection */
      msg_error("Connection failed",
                evt_tag_int("fd", sock),
                evt_tag_str("server", g_sockaddr_format(self->dest_addr, buf2, sizeof(buf2), GSA_FULL)),
                evt_tag_str("local", g_sockaddr_format(self->bind_addr, buf1, sizeof(buf1), GSA_FULL)),
                evt_tag_errno(EVT_TAG_OSERROR, errno),
                NULL);
      close(sock);
      return FALSE;
    }

  return TRUE;
}

void
afsocket_dd_reconnect(AFSocketDestDriver *self)
{
  if (!afsocket_dd_start_connect(self))
    {
      msg_error("Initiating connection failed, reconnecting",
                evt_tag_int("time_reopen", self->time_reopen),
                NULL);
      afsocket_dd_start_reconnect_timer(self);
    }
}

gboolean
afsocket_dd_init(LogPipe *s)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

#if ENABLE_SSL
  if (self->flags & AFSOCKET_REQUIRE_TLS && !self->tls_context)
    {
      msg_error("Transport TLS was specified, but TLS related parameters missing", NULL);
      return FALSE;
    }
#endif
  
  if (cfg)
    {
      self->time_reopen = cfg->time_reopen;
    }
    
  if (!self->writer)
    {
      log_writer_options_init(&self->writer_options, cfg, 0);
      /* NOTE: we open our writer with no fd, so we can send messages down there
       * even while the connection is not established */

      if ((self->flags & AFSOCKET_KEEP_ALIVE))
        self->writer = cfg_persist_config_fetch(cfg, afsocket_dd_format_persist_name(self, self->dest_name, FALSE), NULL, NULL);

      if (!self->writer)
        self->writer = log_writer_new(LW_FORMAT_PROTO | 
#if ENABLE_SSL
                                      (((self->flags & AFSOCKET_STREAM) && !self->tls_context) ? LW_DETECT_EOF : 0) | 
#else
                                      ((self->flags & AFSOCKET_STREAM) ? LW_DETECT_EOF : 0) | 
#endif
                                      (self->flags & AFSOCKET_SYSLOG_PROTOCOL ? LW_SYSLOG_PROTOCOL : 0));
      log_writer_set_options((LogWriter *) self->writer, &self->super.super, &self->writer_options, 0, afsocket_dd_stats_source(self), self->super.id, afsocket_dd_stats_instance(self));
      log_pipe_init(self->writer, NULL);
      log_pipe_append(&self->super.super, self->writer);
    }

  afsocket_dd_reconnect(self);
  return TRUE;
}

gboolean
afsocket_dd_deinit(LogPipe *s)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  if (self->reconnect_timer)
    g_source_remove(self->reconnect_timer);
  if (self->source_id && g_source_remove(self->source_id))
    {
      msg_verbose("Closing connecting fd",
                  evt_tag_int("fd", self->fd),
                  NULL);
      close(self->fd);
    }
  if (self->writer)
    {
      log_pipe_deinit(self->writer);
    }
    
  if (self->flags & AFSOCKET_KEEP_ALIVE)
    {
      cfg_persist_config_add(cfg, afsocket_dd_format_persist_name(self, self->dest_name, FALSE), self->writer, -1, (GDestroyNotify) log_pipe_unref, FALSE);
      self->writer = NULL;
    }

  return TRUE;
}

static void
afsocket_dd_notify(LogPipe *s, LogPipe *sender, gint notify_code, gpointer user_data)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;
  gchar buf[MAX_SOCKADDR_STRING];

  switch (notify_code)
    {
    case NC_CLOSE:
    case NC_WRITE_ERROR:
      log_writer_reopen(self->writer, NULL);

      msg_notice("Syslog connection broken",
                 evt_tag_int("fd", self->fd),
                 evt_tag_str("server", g_sockaddr_format(self->dest_addr, buf, sizeof(buf), GSA_FULL)),
                 evt_tag_int("time_reopen", self->time_reopen),
                 NULL);
      if (self->reconnect_timer)
        {
          g_source_remove(self->reconnect_timer);
          self->reconnect_timer = 0;
        }
      self->reconnect_timer = g_timeout_add(self->time_reopen * 1000, afsocket_dd_reconnect_timer, self);
      break;
    }
}

static gboolean
afsocket_dd_setup_socket(AFSocketDestDriver *self, gint fd)
{
  return afsocket_setup_socket(fd, self->sock_options_ptr, AFSOCKET_DIR_SEND);
}

void
afsocket_dd_free(LogPipe *s)
{
  AFSocketDestDriver *self = (AFSocketDestDriver *) s;

  g_sockaddr_unref(self->bind_addr);
  g_sockaddr_unref(self->dest_addr);
  log_pipe_unref(self->writer);
  g_free(self->hostname);
  log_writer_options_destroy(&self->writer_options);
  g_free(self->dest_name);
  g_free(self->transport);
  log_drv_free(s);
}

void 
afsocket_dd_init_instance(AFSocketDestDriver *self, SocketOptions *sock_options, guint32 flags, gchar *hostname, gchar *dest_name)
{
  log_drv_init_instance(&self->super);
  
  log_writer_options_defaults(&self->writer_options);
  self->super.super.init = afsocket_dd_init;
  self->super.super.deinit = afsocket_dd_deinit;
  self->super.super.queue = log_pipe_forward_msg;
  self->super.super.free_fn = afsocket_dd_free;
  self->super.super.notify = afsocket_dd_notify;
  self->setup_socket = afsocket_dd_setup_socket;
  self->sock_options_ptr = sock_options;
  self->flags = flags  | AFSOCKET_KEEP_ALIVE;
  self->hostname = hostname;
  self->dest_name = dest_name;
}
