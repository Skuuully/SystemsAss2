#include "types.h"
#include "user.h"
#include "batcher.h"

struct Command buffer[COMMAND_BUFFER_SIZE];
int commandCount = 0;

void beginBatching() {
    commandCount = 0;
}

// Should use system call to dump out the contents of the commands, that should loop the calls
void endBatching() {
    if (commandCount > 0) {
        batchGraphics(commandCount, buffer);
    }
}

void AddCommand(struct Command command) {
    buffer[commandCount] = command;
    commandCount++;
    if (commandCount == COMMAND_BUFFER_SIZE) {
        endBatching();
        commandCount = 0;
    }
}

void batchDrawLine(int x0, int y0, int x1, int y1, int colour) {
    if (commandCount >= COMMAND_BUFFER_SIZE) {
        return;
    }

    struct Command command;
    command.x0 = x0;
    command.y0 = y0;
    command.x1 = x1;
    command.y1 = y1;
    command.colour = colour;
    AddCommand(command);
}
