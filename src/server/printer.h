#ifndef __LX_PRINTER_H__
#define __LX_PRINTER_H__

#include <glib.h>

#include "buffer.h"

G_BEGIN_DECLS

void lx_print_int32     (RxBuffer *buf, gint32 value, GError **error);
void lx_print_uint32    (RxBuffer *buf, guint32 value, GError **error);
void lx_print_uint64    (RxBuffer *buf, guint64 value, GError **error);
void lx_print_boolean   (RxBuffer *buf, gboolean value, GError **error);
void lx_print_string    (RxBuffer *buf, gchar *str, GError **error);
void lx_print_str_array (RxBuffer *buf, GPtrArray *str_array, GError **error);

G_END_DECLS

#endif
