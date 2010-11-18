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

#include "logmpx.h"


void
log_multiplexer_add_next_hop(LogMultiplexer *self, LogPipe *next_hop)
{
  /* NOTE: this flag is currently unused. it'll be used to tell whether we can process the multiplexed pipes in parallel threads. */
  if (next_hop->flags & (PIF_FINAL + PIF_FALLBACK))
    self->super.flags &= ~PIF_MPX_INDEP_PATHS;
  g_ptr_array_add(self->next_hops, next_hop);
}

static gboolean
log_multiplexer_init(LogPipe *s)
{
  LogMultiplexer *self = (LogMultiplexer *) s;
  gint i;
  
  for (i = 0; i < self->next_hops->len; i++)
    {
      LogPipe *next_hop = g_ptr_array_index(self->next_hops, i);
          
      if ((next_hop->flags & PIF_FALLBACK) != 0)
        {
          self->fallback_exists = TRUE;
        }
    }
  return TRUE;
}

static gboolean 
log_multiplexer_deinit(LogPipe *self)
{
  return TRUE;
}

static void
log_multiplexer_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options)
{
  LogMultiplexer *self = (LogMultiplexer *) s;
  gint i;
  LogPathOptions local_options = LOG_PATH_OPTIONS_INIT;
  gboolean matched;
  gboolean delivered = FALSE;
  gboolean last_delivery;
  gint fallback;
  
  local_options.matched = &matched;
  
  for (fallback = 0; (fallback == 0) || (fallback == 1 && self->fallback_exists && !delivered); fallback++)
    {
      for (i = 0; i < self->next_hops->len; i++)
        {
          LogPipe *next_hop = g_ptr_array_index(self->next_hops, i);
          LogMessage *next_msg = NULL;

          if (G_UNLIKELY(fallback == 0 && (next_hop->flags & PIF_FALLBACK) != 0))
            {
              continue;
            }
          else if (G_UNLIKELY(fallback && (next_hop->flags & PIF_FALLBACK) == 0))
            {
              continue;
            }
          
          if (self->super.flags & PIF_MPX_FLOW_CTRL_BARRIER)
            local_options.flow_control = (next_hop->flags & PIF_FLOW_CONTROL) ? TRUE : FALSE;
          else
            local_options.flow_control = path_options->flow_control;
            
          matched = TRUE;
          log_msg_add_ack(msg, &local_options);
          
          if (G_UNLIKELY(next_hop->flags & PIF_CLONE))
            {
              if (msg->flags & LF_STATE_REFERENCED)
                {
                  /* if the message is referenced by other clones, we
                   * always have to clone in case a given path
                   * modifies it */
                  next_msg = log_msg_clone_cow(msg, &local_options);
                }
              else
                {
                  /* NOTE: this variable indicates that the upcoming message
                   * delivery is the last one, thus we don't need to clone the
                   * message, a simple ref is enough, provided the message was
                   * not yet cloned. */
                  last_delivery = (self->super.pipe_next == NULL) && (i == self->next_hops->len - 1) && (!self->fallback_exists || delivered || fallback == 1);

                  if (last_delivery)
                    {
                      next_msg = log_msg_ref(msg);
                    }
                  else
                    {
                      next_msg = log_msg_clone_cow(msg, &local_options);
                    }
                }
            }
          else
            next_msg = log_msg_ref(msg);

          log_pipe_queue(next_hop, next_msg, &local_options);
          
          if (matched)
            {
              delivered = TRUE; 
              if (G_UNLIKELY(next_hop->flags & PIF_FINAL))
                break;
            }
        }
    }
  log_pipe_forward_msg(s, msg, path_options);
}

static void
log_multiplexer_free(LogPipe *s)
{
  LogMultiplexer *self = (LogMultiplexer *) s;

  g_ptr_array_free(self->next_hops, TRUE);
  log_pipe_free(s);
}

LogMultiplexer *
log_multiplexer_new(guint32 flags)
{
  LogMultiplexer *self = g_new0(LogMultiplexer, 1);
  
  log_pipe_init_instance(&self->super);
  self->super.init = log_multiplexer_init;
  self->super.deinit = log_multiplexer_deinit;
  self->super.queue = log_multiplexer_queue;
  self->super.free_fn = log_multiplexer_free;
  self->next_hops = g_ptr_array_new();
  self->super.flags = PIF_MPX_INDEP_PATHS | flags;
  return self;
}
