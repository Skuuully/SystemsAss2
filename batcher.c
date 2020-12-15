#include "types.h"
#include "user.h"
#include "batcher.h"

struct Command buffer[COMMAND_BUFFER_SIZE];
int commandCount = 0;

void beginBatching() {
    commandCount = 0;
}

// Checks if we have any commands in the buffer and if so uses system call to output them
void endBatching() {
    if (commandCount > 0) {
        batchGraphics(commandCount, buffer);
    }
}

void AddCommand(union CommandData commandData, int commandType) {
    struct Command command;
    command.commandData = commandData;
    command.unionType = commandType;

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

    struct DrawLineCommand lineCommand;
    lineCommand.x0 = x0;
    lineCommand.y0 = y0;
    lineCommand.x1 = x1;
    lineCommand.y1 = y1;
    lineCommand.colour = colour;

    union CommandData commandData;
    commandData.drawLineCommand = lineCommand;
    AddCommand(commandData, ct_drawLine);
}

void batchDrawCircle(int xCenter, int yCenter, int radius, int colour) {
    if (commandCount >= COMMAND_BUFFER_SIZE) {
        return;
    }

    struct DrawCircleCommand circleCommand;
    circleCommand.xCenter = xCenter;
    circleCommand.yCenter = yCenter;
    circleCommand.radius = radius;
    circleCommand.colour = colour;

    union CommandData commandData;
    commandData.drawCircleCommand = circleCommand;
    AddCommand(commandData, ct_drawCircle);
}
