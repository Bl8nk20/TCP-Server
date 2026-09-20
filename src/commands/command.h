#ifndef COMMAND_H
#define COMMAND_H

#include<stdlib.h>
#include<stddef.h>
#include<sys/socket.h>

typedef struct{
    int client_sock;
    const unsigned char *payload;
    size_t payload_len;
} CommandContext;

typedef struct Command{
    void(*execute)(struct Command *self, const CommandContext *ctx);
    void(*destroy)(struct Command *self);
}Command;

static void command_destroy_common(Command *self){
    free(self);
}

#endif
