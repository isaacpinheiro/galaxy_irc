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

    // inicia aqui pegando um nick
    printf("Escolha um nick: ");
    fgets(buffer, 256, stdin);
    strip(buffer);
    strcat(Me->user_name, buffer);
    memcpy(Me->command, "new_user", sizeof("new_user"));
    memcpy(Me->content, buffer, sizeof(buffer));
    memcpy(buffer, Me, sizeof(Me));
    send(sock, buffer, sizeof(buffer), 0);

    /*
        Mazim, eu fiz esta modificação aqui para enviar para o servidor o nome do novo usuário
        para ser adicionado na lista de usuário. Isto é necessario para a funcionalidade '/list'.
    */
    
    while (1) {

        buffer[0] = '\0';
        Me->content[0] = '\0';
        Me->command[0] = '\0';

        /*
            Mazim, não precisa usar o 'memset' para zerar todo o buffer e as outras strings.
            Basta zerar o primeiro caracter que as funções de '<string.h>' desconsidera o resto.

            Ex: buffer[0] = '\0';

            O 'memset' é uma operação mais custosa do que zerar o primeiro caracter diretamente.
        */

        //memset(Me->content, '\0', 512);
        //memset(Me->command, '\0', 256);
        
        fgets(buffer, 512, stdin);
        strip(buffer);
        xxx(buffer, Me);
        
        // nisso eu nao mexi nada, nao entendi bem como funcionava esse send e o recv

        /*
            Mazim, as funções 'send' e 'recv' são para enviar e receber mensagems do servidor
            TCP. A função 'recv' está sendo utilizada pela 'server_thread' na função 'server_handler'
            no arquivo 'client_cmd.c'. Esta função está sendo executada em uma thread separa porque
            ela não pode ser bloqueado pelas operações da função 'send'. Não altere a função 'server_handler'.

            Obs: depois apague os comentários que eu deixei de resposta.
        */

        memcpy(buffer, Me, sizeof(Me));
        send(sock, buffer, sizeof(buffer), 0);

    }
        

    close(sock);

    return 0;

}

