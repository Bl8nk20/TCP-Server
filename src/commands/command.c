#include "command.h"

void command_destroy_common(Command *self) {
    free(self);
}
