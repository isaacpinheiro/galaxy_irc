#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "client_cmd.h"

int main(int argc, char **argv)
{

    int sock;
    int *new_server_sock;
    struct sockaddr_in server_addr;
    unsigned short server_port = 9000;
    char server_ip[16];
    char buffer[BUFFER_SIZE];
    strcpy(server_ip, argv[1]);
    Message m;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket() failed!");
        exit(-1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect() failed!");
        exit(-1);
    }

    pthread_t server_thread;

    new_server_sock = malloc(1);
    *new_server_sock = sock;

    pthread_create(&server_thread, NULL, server_handler, (void*) new_server_sock);

    printf("Galaxy IRC\n\n");
    printf("Write your nick: ");

    strcpy(m.command, "/new_user");
    fgets(buffer, 256, stdin);
    strip(buffer);
    strcpy(m.user_name, buffer);
    strcpy(m.content, buffer);

    memcpy((void*)buffer, (void*)&m, sizeof(Message));
    send(sock, buffer, sizeof(buffer), 0);

    printf("\n");
    
    while (1) {

        buffer[0] = '\0';
        m.command[0] = '\0';
        m.content[0] = '\0';
        fgets(buffer, 512, stdin);
        strip(buffer);
        parse(buffer, &m);

        if (strcmp(m.command, "/list") == 0) {

            buffer[0] = '\0';
            memcpy((void*)buffer, (void*)&m, sizeof(Message));
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(m.command, "/quit") == 0) {

            buffer[0] = '\0';
            strcpy(m.content, m.user_name);
            memcpy((void*)buffer, (void*)&m, sizeof(Message));
            send(sock, buffer, sizeof(buffer), 0);
            pthread_cancel(server_thread);
            close(sock);
            printf("Disconnected.\n");
            exit(EXIT_SUCCESS);

        } else if (strcmp(m.command, "/kill") == 0) {

            buffer[0] = '\0';
            memcpy((void*)buffer, (void*)&m, sizeof(Message));
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(m.command, "/nick") == 0) {

            buffer[0] = '\0';
            memcpy((void*)buffer, (void*)&m, sizeof(Message));
            send(sock, buffer, sizeof(buffer), 0);
            strcpy(m.user_name, m.content);

        } else {

            buffer[0] = '\0';
            memcpy((void*)buffer, (void*)&m, sizeof(Message));
            send(sock, buffer, sizeof(buffer), 0);

        }

    }

    return 0;

}

