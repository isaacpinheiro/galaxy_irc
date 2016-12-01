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
    struct sockaddr_in server_addr;
    unsigned short server_port = 9000;
    char server_ip[16];
    char buffer[BUFFER_SIZE];
    strcat(server_ip, argv[1]);

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
    pthread_t client_thread;

    pthread_create(&server_thread, NULL, server_handler, (void*) sock);
    pthread_create(&client_thread, NULL, client_handler, (void*) sock);

    /*recv(sock, buffer, sizeof(buffer), 0);
    printf("%s\n\n", buffer);

    while (1) {

        buffer[0] = '\0';
        fgets(buffer, 512, stdin);
        strip(buffer);
        send(sock, buffer, sizeof(buffer), 0);

        recv(sock, buffer, sizeof(buffer), 0);
        printf("%s\n\n", buffer);

    }*/

    close(sock);

    return 0;

}

