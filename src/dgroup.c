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
  
#include "dgroup.h"
#include "misc.h"
#include "stats.h"
#include "messages.h"

#include <sys/time.h>

static gboolean
log_dest_group_init(LogPipe *s)
{
  LogDestGroup *self = (LogDestGroup *) s;
  LogDriver *p;
  gint id = 0;

  for (p = self->drivers; p; p = p->drv_next)
    {
      p->group = g_strdup(self->name);
      if (!p->id)
        p->id = g_strdup_printf("%s#%d", self->name, id++);
      if (!log_pipe_init(&p->super, log_pipe_get_config(s)))
        {
          msg_error("Error initializing dest driver",
                    evt_tag_str("dest", self->name),
                    evt_tag_str("id", p->id),
                    NULL);
          goto deinit_all;
        }
    }
  stats_register_counter(0, SCS_DESTINATION | SCS_GROUP, self->name, NULL, SC_TYPE_PROCESSED, &self->processed_messages);
  return TRUE;

 deinit_all:
  for (p = self->drivers; p; p = p->drv_next)
    log_pipe_deinit(&p->super);
  return FALSE;
}

static gboolean
log_dest_group_deinit(LogPipe *s)
{
  LogDestGroup *self = (LogDestGroup *) s;
  LogDriver *p;
  gboolean success = TRUE;

  stats_unregister_counter(SCS_DESTINATION | SCS_GROUP, self->name, NULL, SC_TYPE_PROCESSED, &self->processed_messages);
  for (p = self->drivers; p; p = p->drv_next)
    {
      if (!log_pipe_deinit(&p->super))
        {
          msg_error("Error deinitializing source driver",
                    evt_tag_str("source", self->name),
                    evt_tag_str("id", p->id),
                    NULL);
          success = FALSE;
        }
    }
  return success;
}

static void
log_dest_group_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options)
{
  LogDestGroup *self = (LogDestGroup *) s;
  LogDriver *p;
  
  for (p = self->drivers; p; p = p->drv_next)
    {
      log_msg_add_ack(msg, path_options);
      log_pipe_queue(&p->super, log_msg_ref(msg), path_options);
    }
  stats_counter_inc(self->processed_messages);
  log_pipe_forward_msg(s, msg, path_options);
}

static void
log_dest_group_free(LogPipe *s)
{
  LogDestGroup *self = (LogDestGroup *) s;
  
  log_drv_unref(self->drivers);
  g_free(self->name);
  log_pipe_free(s);
}

LogDestGroup *
log_dest_group_new(gchar *name, LogDriver *drivers)
{
  LogDestGroup *self = g_new0(LogDestGroup, 1);

  log_pipe_init_instance(&self->super);
  self->name = g_strdup(name);
  self->drivers = drivers;
  self->super.init = log_dest_group_init;
  self->super.deinit = log_dest_group_deinit;
  self->super.queue = log_dest_group_queue;
  self->super.free_fn = log_dest_group_free;
  return self;
}
