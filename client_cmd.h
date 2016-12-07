#ifndef CLIENT_CMD_H
#define CLIENT_CMD_H

#define BUFFER_SIZE 1024

typedef struct Message {
    char user_name[256];
    char command[256];
    char content[512];
} Message;

void strip(char *str);
void *server_handler(void *server_sock);
void parse(char *buffer, Message *Me);

#endif

