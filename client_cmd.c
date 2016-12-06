#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client_cmd.h"

void xxx(char *buffer, Message *Me)
{

    int i = 0;
    int j = 0;

    if (buffer[0] == '/') {

        while (buffer[j] != ' ') {
            Me->command[i] = buffer[j];
            i++;
            j++;
        }

        i=0;
        j++;

        while (buffer[j] != '\0') {
            Me->content[i] = buffer[j];
            i++;
            j++;
        }

    } else {
        strcat(Me->content, buffer);
    }

}

void strip(char *str)
{
    int l = strlen(str) - 1;
    if (str[l] == '\n') str[l] = '\0';
}

void *server_handler(void *server_sock)
{

    int sock = *(int*)server_sock;
    int read_size;
    char buffer[BUFFER_SIZE];

    while ((read_size = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        printf("%s\n\n", buffer);
        buffer[0] = '\0';
    }

}

