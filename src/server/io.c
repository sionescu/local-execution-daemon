#include <unistd.h>
#include <errno.h>

#include <glib.h>
#include <glib/gprintf.h>

#include "error.h"
#include "io.h"

gint
lx_read(gint fd, gpointer buf, gsize len)
{
    gint noctets;
  start:
    noctets = read(fd, buf, len);
    if (noctets < 0) {
        if (errno == EINTR)
            goto start;
        else
            return -1;
    } else {
        return noctets;
    }
}

gint
lx_read_full(gint fd, gpointer buf, gsize len)
{
    gint octets_read = 0;
    guint8 *start = buf;
    while (octets_read < len) {
        gint noctets = lx_read(fd, start, len - octets_read);
        if (noctets < 0) {
            return -1;
        } else if (noctets == 0) {
            goto end;
        } else {
            octets_read += noctets;
            start += noctets;
        }
    }
  end:
    return octets_read;
}

gint
lx_write(gint fd, gpointer buf, gsize len)
{
    gint noctets;
  start:
    noctets = write(fd, buf, len);
    if (noctets < 0) {
        if (errno == EINTR)
            goto start;
        else
            return -1;
    } else {
        return noctets;
    }
}

gint
lx_write_full(gint fd, gpointer buf, gsize len)
{
    gint octets_written = 0;
    guint8 *start = buf;
    while (octets_written < len) {
        gint noctets = lx_write(fd, start, len - octets_written);
        if (noctets < 0) {
            return -1;
        } else {
            octets_written += noctets;
            start += noctets;
        }
    }
    return octets_written;
}

RxBuffer*
lx_read_stream_into_buffer(int fd, RxBuffer *buf, GError **error)
{
    g_assert(buf != NULL); g_assert(error != NULL);

    gint32 total_length;
    gsize datalen = sizeof(gint32);
    gint noctets = lx_read_full(fd, &total_length, datalen);

    if (noctets < 0) {
        LX_ERROR_SYSCALL(error);
        return NULL;
    } else if (noctets < datalen) {
        LX_ERROR_MESSAGE_EOF(error, datalen, noctets);
        return NULL;
    } else {
        total_length = GINT32_FROM_BE(total_length);
        g_printf(" total_length=%d", total_length);
    }

    g_byte_array_set_size(buf->array, total_length);
    lx_read_full(fd, buf->array->data, total_length);
    g_printf(" values:%d,%d,%d,%d",
             (gint)buf->array->data[0], (gint)buf->array->data[1],
             (gint)buf->array->data[2], (gint)buf->array->data[3]);

    return buf;
}
