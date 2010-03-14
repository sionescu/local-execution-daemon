ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -std=c99 -Wall -Wstrict-prototypes

bin_PROGRAMS = src/server/local-execution-daemon

src_server_local_execution_daemon_SOURCES = \
	src/server/lexecd.c src/server/lexecd.h src/server/buffer.c src/server/buffer.h \
	src/server/error.c src/server/error.h src/server/io.c src/server/io.h \
	src/server/printer.c src/server/printer.h src/server/reader.c src/server/reader.h

src_server_local_execution_daemon_LDADD = $(LEXECD_DEP_LIBS)

INCLUDES = $(LEXECD_DEP_CFLAGS)
