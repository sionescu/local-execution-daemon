#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <glib.h>
#include <glib/gprintf.h>

#include "io.h"
#include "reader.h"
#include "printer.h"
#include "lexecd.h"

void print_str(gpointer str, gpointer user_data)
{
    g_printf("[%s]", (gchar*) str);
}

int main(int argc, char *argv[])
{
    g_printf("Socket: create");
    int server_socket = socket(PF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un server_address = { AF_UNIX, "\0init_console" };
    g_printf(" bind");
    bind(server_socket,
         (struct sockaddr *) &server_address,
         sizeof server_address);
    g_printf(" listen");
    listen(server_socket, 1);

    struct sockaddr_un client_address;
    socklen_t client_address_length = sizeof client_address;
    g_printf(" accept");
    int client_connection = accept(server_socket,
                                   (struct sockaddr *) &client_address,
                                   &client_address_length);
    g_printf(" close");
    close(server_socket);

    GError *error = NULL;

    g_printf(" read_buffer:");
    RxBuffer *buf = lx_read_stream_into_buffer(client_connection,
                                               lx_buffer_new(),
                                               &error);
    if (error != NULL) {
        g_printf("\nError message: %s\n", error->message);
        g_error_free(error);
        exit(1);
    }

    g_printf(" read_str_array:");

    GPtrArray *gparray = lx_read_str_array(buf, &error);
    if (error != NULL) {
        g_printf("\nError message: %s\n", error->message);
        g_error_free(error);
        exit(1);
    }

    g_ptr_array_foreach(gparray, print_str, NULL);

    g_printf("\n");

    g_ptr_array_free(gparray, TRUE);
    lx_buffer_free(buf);

    return 0;
}
