#include "types.h"
#include "defs.h"

int sys_getch(void) {
    return consoleget();
}

// TODO: Implement your system call for switching video modes (and any other video-related syscalls)
// in here.

int sys_greeting(void) {
    cprintf("Hello, user\n");
    return 0;
}

int sys_begin(void) {
    consoleSnapshot();
    return 0;
}

int sys_end(void) {
    consoleRevertToSnapshot();
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
    cprintf("line drawn! x0 = %d, x1 = %d\n", x0, x1);

    int dx = x1 - x0;
    if (dx < 0) {
        dx -=  2 * dx;
    }

    int dy = y1 - y0;
    if (dy < 0) {
        dy -=  2 * dy;
    }

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    while(true) {
        consoleSetPixel(x0, y0, colour);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    return 0;
}
