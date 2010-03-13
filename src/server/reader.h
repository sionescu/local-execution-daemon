#ifndef __LX_READER_H__
#define __LX_READER_H__

#include <glib.h>

#include "buffer.h"

G_BEGIN_DECLS

gint32     lx_read_int32     (RxBuffer *buf, GError **error);
guint32    lx_read_uint32    (RxBuffer *buf, GError **error);
guint64    lx_read_uint64    (RxBuffer *buf, GError **error);
gboolean   lx_read_boolean   (RxBuffer *buf, GError **error);
gchar*     lx_read_string    (RxBuffer *buf, GError **error);
GPtrArray* lx_read_str_array (RxBuffer *buf, GError **error);

G_END_DECLS

#endif
