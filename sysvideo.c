#include "types.h"
#include "defs.h"
#include "batcher.h"

int sys_getch(void) {
    return consoleget();
}

// TODO: Implement your system call for switching video modes (and any other video-related syscalls)
// in here.

int sys_greeting(void) {
    cprintf("Hello, user\n");
    return 0;
}

int sys_setvideomode(void) {
    int mode;
    argint(0, &mode);

    consolevgamode(mode);
    consoleClearScreen();
    return 0;
}

int sys_setpixel(void) {
    int x;
    argint(0, &x);
    int y;
    argint(1, &y);
    int colour;
    argint(2, &colour);

    consoleSetPixel(x, y, colour);
    return 0;
}

int sys_drawline(void) {
    int x0;
    argint(0, &x0);
    int y0;
    argint(1, &y0);
    int x1;
    argint(2, &x1);
    int y1;
    argint(3, &y1);
    int colour;
    argint(4, &colour);

    consoleDrawLine(x0, y0, x1, y1, colour);
    return 0;
}

int sys_drawcircle(void) {
    int xCenter;
    argint(0, &xCenter);
    int yCenter;
    argint(1, &yCenter);
    int radius;
    argint(2, &radius);
    int colour;
    argint(3, &colour);

    consoleDrawCircle(xCenter, yCenter, radius, colour);
    return 0;
}

int sys_fillcircle(void) {
    int xCenter;
    argint(0, &xCenter);
    int yCenter;
    argint(1, &yCenter);
    int radius;
    argint(2, &radius);
    int colour;
    argint(3, &colour);

    consoleFillCircle(xCenter, yCenter, radius, colour);
    return 0;
}

int sys_fillrect(void) {
    int xLeft;
    argint(0, &xLeft);
    int yTop;
    argint(1, &yTop);
    int width;
    argint(2, &width);
    int height;
    argint(3, &height);
    int colour;
    argint(4, &colour);

    consoleFillRect(xLeft, yTop, width, height, colour);
    return 0;
}

int sys_drawrect(void) {
    int xLeft;
    argint(0, &xLeft);
    int yTop;
    argint(1, &yTop);
    int width;
    argint(2, &width);
    int height;
    argint(3, &height);
    int colour;
    argint(4, &colour);

    consoleDrawRect(xLeft, yTop, width, height, colour);
    return 0;
}

// Performs all of the commands given by the buffer, used to avoid multiple transitions between ring 3 and 0
int sys_batchGraphics(void) {
    int commandCount;
    argint(0, &commandCount);

    if (commandCount < 0) {
        return 0;
    }

    cprintf("%d Graphics routines performed\n", commandCount);

    struct Command* buffer;
    argptr(1, (void*)&buffer, sizeof(buffer[0]));


    for (int i = 0; i < commandCount && i < COMMAND_BUFFER_SIZE; i++) {
        struct Command command = buffer[i];

        switch (command.unionType) {
        case ct_drawPixel: {
            struct DrawPixelCommand drawPixelCommand = command.commandData.drawPixelCommand;
            consoleSetPixel(drawPixelCommand.x, drawPixelCommand.y, drawPixelCommand.colour);
            break;
        }

        case ct_drawLine: ;
            struct DrawLineCommand drawLineCommand = command.commandData.drawLineCommand;
            consoleDrawLine(drawLineCommand.x0, drawLineCommand.y0, drawLineCommand.x1, drawLineCommand.y1, drawLineCommand.colour);
            break;
        
        case ct_drawCircle: {
            struct DrawCircleCommand drawCircleCommand = command.commandData.drawCircleCommand;
            consoleDrawCircle(drawCircleCommand.xCenter, drawCircleCommand.yCenter, drawCircleCommand.radius, drawCircleCommand.colour);
            break;
        }
        
        case ct_fillCircle: {
            struct DrawCircleCommand drawCircleCommand = command.commandData.drawCircleCommand;
            consoleFillCircle(drawCircleCommand.xCenter, drawCircleCommand.yCenter, drawCircleCommand.radius, drawCircleCommand.colour);
            break;
        }
        
        case ct_drawRect: {
            struct DrawRectCommand drawRectCommand = command.commandData.drawRectCommand;
            consoleDrawRect(drawRectCommand.xLeft, drawRectCommand.yTop, drawRectCommand.width, drawRectCommand.height, drawRectCommand.colour);
            break;
        }

        case ct_fillRect: {
            struct DrawRectCommand drawRectCommand = command.commandData.drawRectCommand;
            consoleFillRect(drawRectCommand.xLeft, drawRectCommand.yTop, drawRectCommand.width, drawRectCommand.height, drawRectCommand.colour);
            break;
        }

        default:
            break;
        }
    }

    return 0;
}
