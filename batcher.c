#include "types.h"
#include "user.h"
#include "batcher.h"

struct Command buffer[COMMAND_BUFFER_SIZE];
int commandCount = 0;

void beginBatching() {
    commandCount = 0;
    memset(buffer, 0, COMMAND_BUFFER_SIZE);
}

// Checks if we have any commands in the buffer and if so uses system call to output them
void endBatching() {
    if (commandCount > 0) {
        batchGraphics(commandCount, buffer);
        commandCount = 0;
    }
}

// Adds a command to the buffer
void AddCommand(union CommandData commandData, int commandType) {
    struct Command command;
    command.commandData = commandData;
    command.unionType = commandType;

    buffer[commandCount] = command;
    commandCount++;
    if (commandCount == COMMAND_BUFFER_SIZE) {
        endBatching();
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

void batchDrawCircle(int xCenter, int yCenter, int radius, int colour, bool fill) {
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

    if (fill) {
        AddCommand(commandData, ct_fillCircle);
    } else {
        AddCommand(commandData, ct_drawCircle);
    }
}

void batchDrawRect(int xLeft, int yTop, int width, int height, int colour, bool fill) {
    if (commandCount >= COMMAND_BUFFER_SIZE) {
        return;
    }

    struct DrawRectCommand rectCommand;
    rectCommand.xLeft = xLeft;
    rectCommand.yTop = yTop;
    rectCommand.width = width;
    rectCommand.height = height;
    rectCommand.colour = colour;

    union CommandData commandData;
    commandData.drawRectCommand = rectCommand;

    if (fill) {
        AddCommand(commandData, ct_fillRect);
    } else {
        AddCommand(commandData, ct_drawRect);
    }
}
