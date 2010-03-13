#include <errno.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "error.h"
#include "io.h"
#include "buffer.h"
#include "reader.h"

gint32
lx_read_int32(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint available_octets = lx_buffer_available_octets(buf);
    guint datalen = sizeof(gint32);

    if (available_octets < datalen) {
        LX_ERROR_MESSAGE_EOF(error, datalen, available_octets);
        return 0;
    }

    gint32 value = GINT32_FROM_BE(*(gint32*)lx_buffer_head_ptr(buf));
    buf->start += sizeof(gint32);

    return value;
}

guint32
lx_read_uint32(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint available_octets = lx_buffer_available_octets(buf);
    guint datalen = sizeof(guint32);

    if (available_octets < datalen) {
        LX_ERROR_MESSAGE_EOF(error, datalen, available_octets);
        return 0;
    }

    guint32 value = GUINT32_FROM_BE(*(guint32*)lx_buffer_head_ptr(buf));
    buf->start += sizeof(guint32);

    return value;
}

guint64
lx_read_uint64(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint available_octets = lx_buffer_available_octets(buf);
    guint datalen = sizeof(guint64);

    if (available_octets < datalen) {
        LX_ERROR_MESSAGE_EOF(error, datalen, available_octets);
        return 0;
    }

    guint64 value = GUINT64_FROM_BE(*(guint64*)lx_buffer_head_ptr(buf));
    buf->start += sizeof(guint64);

    return value;
}

gboolean
lx_read_boolean(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint32 value = lx_read_uint32(buf, error);

    if (value == 0)
        return FALSE;
    else
        return TRUE;
}

gchar*
lx_read_string(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint32 datalen = lx_read_uint32(buf, error);
    if (*error != NULL)
        return NULL;

    if (datalen > LX_MAX_STRING_LENGTH) {
        LX_ERROR_STRING_TOO_LONG(error,datalen);
        return NULL;
    }

    gchar *start_ptr = (gchar*)lx_buffer_head_ptr(buf);

    for (guint i = 0; i < datalen - 1; i++) {
        if (start_ptr[i] == '\0') {
            LX_ERROR_STRING_CONTAINS_NULL_OCTETS(error, i);
            return NULL;
        }
    }

    if (start_ptr[datalen] != '\0') {
        LX_ERROR_STRING_NOT_NULL_TERMINATED(error, start_ptr[datalen]);
        return NULL;
    }
    
    guint available_octets = lx_buffer_available_octets(buf);

    if (available_octets < datalen) {
        LX_ERROR_MESSAGE_EOF(error, datalen, available_octets);
        return NULL;
    }

    gchar *str = g_strndup(start_ptr, datalen);
    buf->start += datalen;

    return str;
}

GPtrArray*
lx_read_str_array(RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    guint32 datalen = lx_read_uint32(buf, error);
    if (*error != NULL)
        return NULL;

    GPtrArray *gparray = g_ptr_array_new_with_free_func(g_free);
    for (guint i = 0; i < datalen; i++) {
        gchar *str = lx_read_string(buf, error);
        if (*error != NULL)
            return NULL;
        g_ptr_array_add(gparray, (gpointer) str);
    }

    return gparray;
}
