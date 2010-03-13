#ifndef __LX_ERROR_H__
#define __LX_ERROR_H__

#include <glib.h>

G_BEGIN_DECLS

GQuark lx_syscall_error_quark(void);
#define LX_SYSCALL_ERROR  lx_syscall_error_quark()

GQuark lx_app_error_quark(void);
#define LX_APP_ERROR      lx_app_error_quark()

typedef enum {
    LX_MESSAGE_EOF,
    LX_STRING_TOO_LONG,
    LX_STRING_CONTAINS_NULL_OCTETS,
    LX_STRING_NOT_NULL_TERMINATED
} RxAppError;

#define LX_ERROR_SYSCALL(error) \
  g_set_error(error, \
              LX_SYSCALL_ERROR, \
              errno, \
              "Failed total_length read exec command: %s", \
              g_strerror(errno))

#define LX_ERROR_MESSAGE_EOF(error,octets_needed,octets_available)    \
  g_set_error(error, \
              LX_APP_ERROR, \
              LX_MESSAGE_EOF, \
              "Trying to read %d octets, only %d available", \
              (gint)(octets_needed), (gint)(octets_available))

#define LX_ERROR_STRING_TOO_LONG(error,length)    \
  g_set_error(error, \
              LX_APP_ERROR, \
              LX_STRING_TOO_LONG, \
              "String length %u is larger than the maximum allowed %u", \
              (guint)(length), LX_MAX_STRING_LENGTH)

#define LX_ERROR_STRING_CONTAINS_NULL_OCTETS(error,index)    \
  g_set_error(error, \
              LX_APP_ERROR, \
              LX_STRING_TOO_LONG, \
              "String contains null octets at index %d", \
              (gint)(index))

#define LX_ERROR_STRING_NOT_NULL_TERMINATED(error,octet)     \
  g_set_error(error, \
              LX_APP_ERROR, \
              LX_STRING_TOO_LONG, \
              "String has non-zero final octet: %d", \
              (gint)(octet))

G_END_DECLS

#endif
