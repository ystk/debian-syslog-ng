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
  
#ifndef LOG_WRITER_H_INCLUDED
#define LOG_WRITER_H_INCLUDED

#include "logpipe.h"
#include "templates.h"
#include "logqueue.h"
#include "logproto.h"
#include "timeutils.h"

/* writer constructor flags */
#define LW_DETECT_EOF      0x0001
#define LW_FORMAT_FILE     0x0002
#define LW_FORMAT_PROTO    0x0004
#define LW_ALWAYS_WRITABLE 0x0008
#define LW_SYSLOG_PROTOCOL 0x0010

/* writer options (set by the user) */
#define LWO_SYSLOG_PROTOCOL   0x0001
#define LWO_NO_MULTI_LINE     0x0002
/* we don't want to have a dropped counter for this writer */
#define LWO_NO_STATS        0x0004
/* several writers use the same counter */
#define LWO_SHARE_STATS     0x0008

typedef struct _LogWriterOptions
{
  /* bitmask of LWO_* */
  guint32 options;
  
  /* maximum number of entries in the memory based FIFO */
  gint mem_fifo_size;
  
  /* minimum number of entries to trigger a flush */
  gint flush_lines;
  
  /* flush anyway if this time was elapsed */
  gint flush_timeout;
  LogTemplate *template;
  LogTemplate *file_template;
  LogTemplate *proto_template;
  
  gboolean use_time_recvd; /* deprecated */
  gboolean fsync;
  gshort ts_format;
  gchar *send_time_zone;
  TimeZoneInfo *send_time_zone_info;

  gshort frac_digits;
  gint throttle; /* messages per sec, 0 means unlimited */
  gint time_reopen;
  gint suppress;
} LogWriterOptions;

typedef struct _LogWriter
{
  LogPipe super;
  GSource *source;
  LogQueue *queue;
  guint32 flags;
  gint32 seq_num;
  guint32 *dropped_messages;
  guint32 *suppressed_messages;
  guint32 *processed_messages;
  guint32 *stored_messages;
  gint throttle_buckets;
  LogPipe *control;
  LogWriterOptions *options;
  LogMessage *last_msg;
  guint32 last_msg_count;
  guint last_msg_timerid;

  gint stats_level;
  guint16 stats_source;
  gchar *stats_id;
  gchar *stats_instance;
} LogWriter;

void log_writer_set_options(LogWriter *self, LogPipe *control, LogWriterOptions *options, gint stats_level, gint stats_source, const gchar *stats_id, const gchar *stats_instance);
void log_writer_format_log(LogWriter *self, LogMessage *lm, GString *result);
gboolean log_writer_reopen(LogPipe *s, LogProto *proto);
LogPipe *log_writer_new(guint32 flags);

void log_writer_options_set_template_escape(LogWriterOptions *options, gboolean enable);
void log_writer_options_defaults(LogWriterOptions *options);
void log_writer_options_init(LogWriterOptions *options, GlobalConfig *cfg, guint32 option_flags);
void log_writer_options_destroy(LogWriterOptions *options);
gint log_writer_options_lookup_flag(const gchar *flag);

#endif
