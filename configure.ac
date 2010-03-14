dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([Local Execution Daemon], [0.1], [iolib-devel@common-lisp.net])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign silent-rules subdir-objects])

dnl Have Kbuild-like build output
AM_SILENT_RULES([yes])

# Minimum Autoconf version required.
AC_PREREQ(2.60)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.h.in])
AC_CONFIG_SRCDIR([src/server/lexecd.c])

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC

# required versions of other packages
m4_define([glib_required_version], [2.22.0])

dnl Checks for header files.
AC_CHECK_HEADER_STRICT(stdlib.h)
AC_CHECK_HEADER_STRICT(string.h)
AC_CHECK_HEADER_STRICT(unistd.h)
AC_CHECK_HEADER_STRICT(sys/socket.h)

PKG_CHECK_MODULES(GLIB,
  [glib-2.0 >= glib_required_version])

LEXECD_DEP_CFLAGS=`$PKG_CONFIG glib-2.0 --cflags`
LEXECD_DEP_LIBS=`$PKG_CONFIG glib-2.0 --libs`

AC_SUBST(LEXECD_DEP_CFLAGS)
AC_SUBST(LEXECD_DEP_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
