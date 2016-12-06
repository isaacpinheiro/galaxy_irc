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
    strcat(server_ip, argv[1]);
    Message *Me = (Message*) malloc(sizeof(Message));

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

    Me->user_name[0] = '\0';
    Me->command[0] = '\0';
    Me->content[0] = '\0';

    printf("Galaxy IRC\n\n");
    printf("Escolha um nick: ");

    buffer[0] = '\0';
    memcpy(buffer, "/new_user", sizeof(buffer));
    send(sock, buffer, sizeof(buffer), 0);

    buffer[0] = '\0';
    fgets(buffer, 256, stdin);
    strip(buffer);
    memcpy(Me->user_name, buffer, sizeof(buffer));
    send(sock, buffer, sizeof(buffer), 0);

    printf("\n");
    
    while (1) {

        buffer[0] = '\0';
        Me->command[0] = '\0';
        Me->content[0] = '\0';
        fgets(buffer, 512, stdin);
        strip(buffer);
        xxx(buffer, Me);

        if (strcmp(Me->command, "/list") == 0) {

            buffer[0] = '\0';
            memcpy(buffer, Me->command, sizeof(Me->command));
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(Me->command, "/quit") == 0) {

            buffer[0] = '\0';
            memcpy(buffer, Me->command, sizeof(Me->command));
            send(sock, buffer, sizeof(buffer), 0);

            buffer[0] = '\0';
            memcpy(buffer, Me->user_name, sizeof(Me->user_name));
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(Me->command, "/kill") == 0) {

            buffer[0] = '\0';
            memcpy(buffer, Me->command, sizeof(Me->command));
            send(sock, buffer, sizeof(buffer), 0);

            buffer[0] = '\0';
            memcpy(buffer, Me->content, sizeof(Me->content));
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(Me->command, "/nick") == 0) {

            buffer[0] = '\0';
            memcpy(buffer, Me->command, sizeof(Me->command));
            send(sock, buffer, sizeof(buffer), 0);

            buffer[0] = '\0';
            memcpy(buffer, Me->user_name, sizeof(Me->user_name));
            send(sock, buffer, sizeof(buffer), 0);

            buffer[0] = '\0';
            memcpy(buffer, Me->content, sizeof(Me->content));
            send(sock, buffer, sizeof(buffer), 0);

            Me->user_name[0] = '\0';
            memcpy(Me->user_name, Me->content, sizeof(Me->content));

        } else {

            buffer[0] = '\0';
            memcpy(buffer, Me->content, sizeof(Me->command));
            send(sock, buffer, sizeof(buffer), 0);

        }

    }

    return 0;

}

