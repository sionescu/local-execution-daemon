#ifndef __LX_BUFFER_H__
#define __LX_BUFFER_H__

#include <glib.h>

G_BEGIN_DECLS

#define LX_MAX_STRING_LENGTH 65536

struct _RxBuffer {
    GByteArray *array;
    guint start;
};

typedef struct _RxBuffer RxBuffer;

RxBuffer* lx_buffer_new(void);
void      lx_buffer_free(RxBuffer *buf);

guint     lx_buffer_available_octets(RxBuffer *buf);
gpointer  lx_buffer_head_ptr(RxBuffer *buf);

G_END_DECLS

#endif
