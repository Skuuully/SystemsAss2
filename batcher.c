#include "types.h"
#include "user.h"
#include "batcher.h"

struct Command buffer[COMMAND_BUFFER_SIZE];
int commandCount = 0;
bool active = false;

void beginBatching() {
    commandCount = 0;
    memset(buffer, 0, COMMAND_BUFFER_SIZE);
    active = true;
}

// Checks if we have any commands in the buffer and if so uses system call to output them, disables future calls from batching until re-enabled
void endBatching() {
    if (commandCount > 0) {
        batchGraphics(commandCount, buffer);
        commandCount = 0;
    }

    active = false;
}

// Checks if there are any commands in the buffer and if so pumps them out, maintains that the batcher is active so that future calls are still batched
void internalEndBatch() {
    if (commandCount > 0) {
        batchGraphics(commandCount, buffer);
        commandCount = 0;
    }
}

// Adds a command to the buffer
void addCommand(union CommandData commandData, int commandType) {
    struct Command command;
    command.commandData = commandData;
    command.unionType = commandType;

    buffer[commandCount] = command;
    commandCount++;
    if (commandCount == COMMAND_BUFFER_SIZE) {
        internalEndBatch();
    }
}

// Adds a draw line command to the buffer with the given parameters
void batchDrawPixel(int x, int y, int colour) {
    if (!active) {
        setpixel(x, y, colour);
        return;
    }

    if (commandCount >= COMMAND_BUFFER_SIZE) {
        return;
    }

    struct DrawPixelCommand pixelCommand;
    pixelCommand.x = x;
    pixelCommand.y = y;
    pixelCommand.colour = colour;

    union CommandData commandData;
    commandData.drawPixelCommand = pixelCommand;
    addCommand(commandData, ct_drawPixel);
}

// Adds a draw line command to the buffer with the given parameters
void batchDrawLine(int x0, int y0, int x1, int y1, int colour) {
    if (!active) {
        drawline(x0, y0, x1, y1, colour);
        return;
    }

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
    addCommand(commandData, ct_drawLine);
}

// Adds the appropiate draw circle command to the buffer with the correct parameters and type
void batchDrawCircle(int xCenter, int yCenter, int radius, int colour, bool fill) {
    if (!active) {
        if (fill) {
            fillcircle(xCenter, yCenter, radius, colour);
        } else {
            drawcircle(xCenter, yCenter, radius, colour);
        }
        return;
    }

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

    int type = fill ? ct_fillCircle : ct_drawCircle;
    addCommand(commandData, type);
}

// Adds the appropiate draw rectangle command to the buffer with the correct parameters and type
void batchDrawRect(int xLeft, int yTop, int width, int height, int colour, bool fill) {
    if (!active) {
        if (fill) {
            fillrect(xLeft, yTop, width, height, colour);
        } else {
            drawrect(xLeft, yTop, width, height, colour);
        }
        return;
    }

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

    int type = fill ? ct_fillRect : ct_drawRect;
    addCommand(commandData, type);
}
