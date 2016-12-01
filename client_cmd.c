#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client_cmd.h"

void strip(char *str)
{
    int l = strlen(str) - 1;
    if (str[l] == '\n') str[l] = '\0';
}

void *server_handler(void *server_sock)
{

}

void *client_handler(void *client_sock)
{

    while (1) {

        buffer[0] = '\0';
        fgets(buffer, 512, stdin);
        strip(buffer);
        send(sock, buffer, sizeof(buffer), 0);

    }

}

