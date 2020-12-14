#include "types.h"
#include "user.h"

#define COMMAND_BUFFER_SIZE 1000

struct Command {
    int x0;
    int y0;
    int x1;
    int y1;
    int colour;
};

struct Command* buffer[COMMAND_BUFFER_SIZE];
int commandCount = 0;

void beginBatching() {
    commandCount = 0;
}

void endBatching() {
    for (int i = 0; i < commandCount && i < COMMAND_BUFFER_SIZE; i++) {
        struct Command* command = buffer[i];
        if (!command) {
            continue;
        }

        drawline(command->x0, command->y0, command->x1, command->y1, command->colour);
        free(command);
    }
}

void drawLine(int x0, int y0, int x1, int y1, int colour) {
    if (commandCount >= COMMAND_BUFFER_SIZE) {
        return;
    }

    struct Command *command = malloc(sizeof(struct Command));
    command->x0 = x0;
    command->y0 = y0;
    command->x1 = x1;
    command->y1 = y1;
    command->colour = colour;
    buffer[commandCount] = command;
    commandCount++;
    //printf(1, "x0: %d, y0: %d, x1: %d, y1: %d, colour: %d\n", command.x0, command.y0, command.x1, command.y1, command.colour);
}

