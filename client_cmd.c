#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client_cmd.h"

void xxx (char *buffer, Message *Me) {
    int i = 0;
     
    if (buffer[0] == '/') {
        buffer++;
        
        while (*buffer != ' ') {
            Me->command[i] = *buffer;
            i++;
            ++buffer;
        }
            
        i=0;
        buffer++;
        while (*buffer != '\0') {
            Me->content[i] = *buffer;
            i++;
            ++buffer;
        }
            
    } else {
        strcat(Me->content, buffer);
    }
    
    printf("Nome: %s  Comando: %s  Mensagem: %s\n", Me->user_name, Me->command, Me->content);
        
}

void strip(char *str)
{
    int l = strlen(str) - 1;
    if (str[l] == '\n') str[l] = '\0';
}


//tentei nao mexer em nada aqui
void *server_handler(void *server_sock)
{

    int sock = *(int*)server_sock;
    int read_size;
    char buffer[BUFFER_SIZE];

    while ((read_size = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        
        memset(buffer, '\0', 512);
    }

}



