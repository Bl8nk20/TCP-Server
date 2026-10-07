#include "command.h"

typedef struct{
    Command base;
} DungeonCommand;

static void execute_dungeon(Command *self, const CommandContext *ctx){
    (void)self;
    


    // Empfangene Daten zurücksenden an Client
    send(ctx->client_sock, ctx->payload, ctx->payload_len, 0);
}

Command* create_dungeon_command(void){
    DungeonCommand *cmd = malloc(sizeof(DungeonCommand));
    if(!cmd){
        return NULL;
    }
    cmd->base.execute = execute_dungeon;
    cmd->base.destroy = command_destroy_common;
    return (Command *)cmd;
}
