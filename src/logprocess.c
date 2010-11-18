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

#include "logprocess.h"
#include <string.h>

void
log_process_rule_init(LogProcessRule *self, const gchar *name)
{
  memset(self, 0, sizeof(LogProcessRule));
  self->ref_cnt = 1;
  self->name = g_strdup(name);

}

void
log_process_rule_ref(LogProcessRule *self)
{ 
  self->ref_cnt++;
}

void
log_process_rule_unref(LogProcessRule *self)
{
  if (--self->ref_cnt == 0)
    {
      if (self->free_fn)
        self->free_fn(self);
      g_free(self->name);
      g_free(self);
    }
}

static gboolean
log_process_pipe_init(LogPipe *self)
{
  return TRUE;
}

static gboolean 
log_process_pipe_deinit(LogPipe *self)
{
  return TRUE;
}

static void
log_process_pipe_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options)
{
  LogProcessPipe *self = (LogProcessPipe *) s;
  if (log_process_rule_process(self->rule, msg))
    {
      /* forward message */
      if (s->pipe_next)
        log_pipe_queue(s->pipe_next, msg, path_options);
      else
        log_msg_drop(msg, path_options);
    }
  else
    {
      if (path_options->matched)
        (*path_options->matched) = FALSE;
      log_msg_drop(msg, path_options);
    }
}

static void
log_process_pipe_free(LogPipe *s)
{
  LogProcessPipe *self = (LogProcessPipe *) s;
  
  log_process_rule_unref(self->rule);
  log_pipe_free(s);
}

LogPipe *
log_process_pipe_new(LogProcessRule *rule)
{
  LogProcessPipe *self = g_new0(LogProcessPipe, 1);
  
  log_pipe_init_instance(&self->super);
  log_process_rule_ref(rule);
  self->rule = rule;
  self->super.init = log_process_pipe_init;
  self->super.deinit = log_process_pipe_deinit;
  self->super.queue = log_process_pipe_queue;
  self->super.free_fn = log_process_pipe_free;
  return &self->super;
}

