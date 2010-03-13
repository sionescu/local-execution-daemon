#include "buffer.h"

RxBuffer*
lx_buffer_new()
{
    RxBuffer *buf = g_new(RxBuffer, 1);
    buf->array = g_byte_array_new();
    buf->start = 0;

    return buf;
}

void
lx_buffer_free(RxBuffer *buf)
{
    if (buf == NULL) return;

    if (buf->array != NULL) {
        g_byte_array_free(buf->array, TRUE);
        buf->array = NULL;
    }
    g_free(buf);
}

guint
lx_buffer_available_octets(RxBuffer *buf)
{
    return buf->array->len - buf->start;
}

gpointer
lx_buffer_head_ptr(RxBuffer *buf)
{
    return (gpointer)buf->array->data + buf->start;
}
