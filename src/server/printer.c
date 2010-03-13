#ifdef __linux__
#define _GNU_SOURCE
#endif

#include <string.h>

#include "error.h"
#include "buffer.h"
#include "io.h"
#include "printer.h"

void
lx_print_int32(RxBuffer *buf, gint32 value, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(error != NULL);

    gint32 network_value = GINT32_TO_BE(value);
    g_byte_array_append(buf->array, (guint8*)&network_value, sizeof(network_value));
}

void
lx_print_uint32(RxBuffer *buf, guint32 value, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(error != NULL);

    guint32 network_value = GUINT32_TO_BE(value);
    g_byte_array_append(buf->array, (guint8*)&network_value, sizeof(network_value));
}

void
lx_print_uint64(RxBuffer *buf, guint64 value, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(error != NULL);

    guint64 network_value = GUINT64_TO_BE(value);
    g_byte_array_append(buf->array, (guint8*)&network_value, sizeof(network_value));
}

void
lx_print_boolean(RxBuffer *buf, gboolean value, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(error != NULL);

    lx_print_uint32(buf, (guint32)value, error);
}

void
lx_print_string(RxBuffer *buf, gchar *str, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(str != NULL); g_assert(error != NULL);

    gsize datalen = strnlen(str, LX_MAX_STRING_LENGTH + 1);
    if (datalen >= LX_MAX_STRING_LENGTH) {
        LX_ERROR_STRING_TOO_LONG(error,datalen);
        return;
    }

    lx_print_uint32(buf, (guint32)datalen+1, error);
    g_byte_array_append(buf->array, (guint8*)str, datalen+1);
}

void
lx_print_str_array(RxBuffer *buf, GPtrArray *str_array, GError **error)
{
    g_assert(buf != NULL); g_assert(buf->array != NULL);
    g_assert(str_array != NULL); g_assert(error != NULL);

    guint datalen = str_array->len;
    lx_print_uint32(buf, (guint32)datalen, error);

    for (guint i = 0; i < datalen; i++) {
        lx_print_string(buf, (gchar*)str_array->pdata[i], error);
        if (*error != NULL)
            return;
    }
}
