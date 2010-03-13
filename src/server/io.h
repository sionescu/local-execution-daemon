#ifndef __LX_IO_H__
#define __LX_IO_H__

#include <glib.h>

#include "buffer.h"

G_BEGIN_DECLS

gint lx_read       (gint fd, gpointer buf, gsize len);
gint lx_read_full  (gint fd, gpointer buf, gsize len);
gint lx_write      (gint fd, gpointer buf, gsize len);
gint lx_write_full (gint fd, gpointer buf, gsize len);

RxBuffer* lx_read_stream_into_buffer   (gint fd, RxBuffer *buf, GError **error);
RxBuffer* lx_read_datagram_into_buffer (gint fd, RxBuffer *buf, GError **error);

G_END_DECLS

#endif
