#include <glib.h>

#include "error.h"

GQuark
lx_syscall_error_quark(void)
{
  return g_quark_from_static_string ("lexecd-syscall-error-quark");
}

GQuark
lx_app_error_quark(void)
{
  return g_quark_from_static_string ("lexecd-app-error-quark");
}
