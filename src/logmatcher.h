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

#ifndef LOGMATCHER_H_INCLUDED
#define LOGMATCHER_H_INCLUDED

#include "logmsg.h"
#include "templates.h"

enum
{
  LMR_POSIX_REGEXP,
  LMR_PCRE_REGEXP,
  LMR_STRING,
  LMR_GLOB,
};

enum
{
  /* use global search/replace */
  /* use global search/replace */
  LMF_GLOBAL = 0x0001,
  LMF_ICASE  = 0x0002,
  LMF_MATCH_ONLY = 0x0004,

  /* POSIX + PCRE common flags */
  LMF_NEWLINE= 0x0008,
  LMF_UTF8   = 0x0010,
  LMF_STORE_MATCHES = 0x0020,
  LMF_VALID_REGEXP_FLAGS = 0x0037,

  /* string flags */
  LMF_SUBSTRING = 0x0040,
  LMF_PREFIX = 0x0080,
  LMF_VALID_STRING_FLAGS = 0x00C7,
};

typedef struct _LogMatcher LogMatcher;

struct _LogMatcher
{
  gint type;
  gint flags;
  gboolean (*compile)(LogMatcher *s, const gchar *re);
  /* value_len can be -1 to indicate unknown length */
  gboolean (*match)(LogMatcher *s, LogMessage *msg, gint value_handle, const gchar *value, gssize value_len);
  /* value_len can be -1 to indicate unknown length, new_length can be returned as -1 to indicate unknown length */
  gchar *(*replace)(LogMatcher *s, LogMessage *msg, gint value_handle, const gchar *value, gssize value_len, LogTemplate *replacement, gssize *new_length);
  void (*free_fn)(LogMatcher *s);
};

static inline gboolean 
log_matcher_compile(LogMatcher *s, const gchar *re)
{
  return s->compile(s, re);
}

static inline gboolean
log_matcher_match(LogMatcher *s, LogMessage *msg, gint value_handle, const gchar *value, gssize value_len)
{
  return s->match(s, msg, value_handle, value, value_len);
}

static inline gchar *
log_matcher_replace(LogMatcher *s, LogMessage *msg, gint value_handle, const gchar *value, gssize value_len, LogTemplate *replacement, gssize *new_length)
{
  if (s->replace)
    return s->replace(s, msg, value_handle, value, value_len, replacement, new_length);
  return NULL;
}

static inline void
log_matcher_free(LogMatcher *s)
{
  if (s->free_fn)
    s->free_fn(s);
  g_free(s);
}

static inline void
log_matcher_set_flags(LogMatcher *s, gint flags)
{
  s->flags = flags;
}

gint log_matcher_lookup_flag(const gchar* flag);

LogMatcher *log_matcher_posix_re_new(void);
LogMatcher *log_matcher_pcre_re_new(void);
LogMatcher *log_matcher_string_new(void);
LogMatcher *log_matcher_glob_new(void);

LogMatcher *log_matcher_new(const gchar *type);

#endif
