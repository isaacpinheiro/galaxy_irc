#ifndef CLIENT_CMD_H
#define CLIENT_CMD_H

#define BUFFER_SIZE 1024

void strip(char *str);

void *server_handler(void *server_sock);
void *client_handler(void *client_sock);

#endif

