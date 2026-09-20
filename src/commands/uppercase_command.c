#include<ctype.h>

#include "command.h"

typedef struct{
    Command base;
} UpperCommand;

static void execute_upper(Command *self, const CommandContext *ctx){
    (void)self;

    char buffer[1024] = {0};
    size_t len = ctx->payload_len < sizeof(buffer) ? ctx->payload_len : sizeof(buffer) - 1;

    for(size_t i = 0; i < len; i++){
        buffer[i] = toupper(ctx->payload[i]);
    }

    send(ctx->client_sock, buffer, len, 0);
}

Command* create_uppercase_command(void){
    UpperCommand *cmd = malloc(sizeof(UpperCommand));
    if(!cmd){
        return NULL;
    }
    cmd->base.execute = execute_upper;
    cmd->base.destroy = command_destroy_common;

    return (Command*)cmd;
}
