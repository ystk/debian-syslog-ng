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
  
#include "afuser.h"
#include "alarms.h"
#include "messages.h"

#include <utmp.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef HAVE_GETUTENT
#include "utils.h"
#endif

typedef struct _AFUserDestDriver
{
  LogDriver super;
  GString *username;
  time_t disable_until;
} AFUserDestDriver;

static gboolean
afuser_dd_init(LogPipe *s)
{
  return TRUE;
}

static gboolean
afuser_dd_deinit(LogPipe *s)
{
  return TRUE;
}

static void
afuser_dd_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options)
{
  AFUserDestDriver *self = (AFUserDestDriver *) s;
  gchar buf[8192];
  struct utmp *ut;
  GString *timestamp;
  time_t now;
  
  now = msg->timestamps[LM_TS_RECVD].time.tv_sec;
  if (self->disable_until && self->disable_until > now)
    goto finish;
  
  timestamp = g_string_sized_new(0);
  log_stamp_format(&msg->timestamps[LM_TS_STAMP], timestamp, TS_FMT_FULL, -1, 0);
  g_snprintf(buf, sizeof(buf), "%s %s %s\n",
             timestamp->str,
             log_msg_get_value(msg, LM_V_HOST, NULL),
             log_msg_get_value(msg, LM_V_MESSAGE, NULL));
  g_string_free(timestamp, TRUE);
  
  /* NOTE: there's a private implementations of getutent in utils.c on Systems which do not provide one. */
  while ((ut = getutent())) 
    {
#if HAVE_MODERN_UTMP
      if (ut->ut_type == USER_PROCESS &&
          ((self->username->len == 1 &&
            self->username->str[0] == '*') ||
           (self->username->len <= sizeof(ut->ut_user) &&
            memcmp(self->username->str, ut->ut_user, self->username->len) == 0))) 
#else
      if ((self->username->len == 1 &&
           self->username->str[0] == '*') ||
          (self->username->len <= sizeof(ut->ut_name) &&
           memcmp(self->username->str, ut->ut_name, self->username->len) == 0)) 
#endif
        {
          gchar line[128];
          gchar *p = line;
          int fd;

          if (ut->ut_line[0] != '/')
            {
              strcpy(line, "/dev/");
              p = line + 5;
            }
          else
            line[0] = 0;
          strncpy(p, ut->ut_line, sizeof(line) - (p - line));
          fd = open(line, O_NOCTTY | O_APPEND | O_WRONLY | O_NONBLOCK);
          if (fd != -1) 
            {
              alarm_set(10);
              if (write(fd, buf, strlen(buf)) < 0 && errno == EINTR && alarm_has_fired())
                {
                  msg_notice("Writing to the user terminal has blocked for 10 seconds, disabling for 10 minutes",
                            evt_tag_str("user", self->username->str),
                            NULL);
                  self->disable_until = now + 600;
                }
              alarm_cancel();
              close(fd);
            }
        }
    }
  endutent();
finish:
  log_msg_ack(msg, path_options);
  log_msg_unref(msg);
}

LogDriver *
afuser_dd_new(gchar *user)
{
  AFUserDestDriver *self = g_new0(AFUserDestDriver, 1);
  
  log_drv_init_instance(&self->super);
  self->super.super.init = afuser_dd_init;
  self->super.super.deinit = afuser_dd_deinit;
  self->super.super.queue = afuser_dd_queue;
  self->username = g_string_new(user);
  return &self->super;
}
