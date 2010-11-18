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

#ifndef SERIALIZE_H_INCLUDED
#define SERIALIZE_H_INCLUDED

#include "syslog-ng.h"
#include <stdio.h>

typedef struct _SerializeArchive SerializeArchive;

struct _SerializeArchive
{
  GError *error;
  
  gboolean (*read_bytes)(SerializeArchive *archive, gchar *buf, gsize count, GError **error);
  gboolean (*write_bytes)(SerializeArchive *archive, const gchar *buf, gsize count, GError **error);
};

gboolean serialize_write_blob(SerializeArchive *archive, const void *blob, gsize len);
gboolean serialize_read_blob(SerializeArchive *archive, void *blob, gsize len);
gboolean serialize_write_string(SerializeArchive *archive, GString *str);
gboolean serialize_read_string(SerializeArchive *archive, GString *str);
gboolean serialize_write_cstring(SerializeArchive *archive, const gchar *str, gssize len);
gboolean serialize_read_cstring(SerializeArchive *archive, gchar **str, gsize *strlen);
gboolean serialize_write_uint64(SerializeArchive *archive, guint64 value);
gboolean serialize_read_uint64(SerializeArchive *archive, guint64 *value);
gboolean serialize_write_uint32(SerializeArchive *archive, guint32 value);
gboolean serialize_read_uint32(SerializeArchive *archive, guint32 *value);
gboolean serialize_write_uint16(SerializeArchive *archive, guint16 value);
gboolean serialize_read_uint16(SerializeArchive *archive, guint16 *value);
gboolean serialize_write_uint8(SerializeArchive *archive, guint8 value);
gboolean serialize_read_uint8(SerializeArchive *archive, guint8 *value);

SerializeArchive *serialize_file_archive_new(FILE *f);
SerializeArchive *serialize_string_archive_new(GString *str);
void serialize_archive_free(SerializeArchive *self);

#endif
