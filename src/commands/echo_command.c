#include "command.h"

typedef struct{
    Command base;
} EchoCommand;

static void execute_echo(Command *self, const CommandContext *ctx){
    (void)self;
    // Empfangene Daten zurücksenden an Client
    send(ctx->client_sock, ctx->payload, ctx->payload_len, 0);
}

Command* create_echo_command(void){
    EchoCommand *cmd = malloc(sizeof(EchoCommand));
    if(!cmd){
        return NULL;
    }
    cmd->base.execute = execute_echo;
    cmd->base.destroy = command_destroy_common;
    return (Command *)cmd;
}
