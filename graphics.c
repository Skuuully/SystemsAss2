#include "types.h"
#include "user.h"

void beginBatching();
void endBatching();
void drawLine(int x0, int y0, int x1, int y1, int colour);

int main() {
    begin();
    beginBatching();

    setvideomode(0x12);

    int off = 20;
    for (int i = off; i < off + 20; i++) {
        for (int j = 0; j < 16; j++) {
            drawLine(0 + i + (j * off), 0, 0 + i + (j * off), 200, j);
        }
    }

    for (int i = 0; i < 16; i++) {
        drawLine(0, 20 + (i * 3), 640, 20 + (i * 3), i);
    }

    // Keep me uncommented
    // // drawline(100, 100, 200, 200, 0);
    // // drawline(0, 0, 0, 20, 1);
    // // drawline(0, 0, 100, 100, 2);
    // // drawline(10, 0, 30, 0, 3);
    // // drawline(100, 100, 120, 20, 4);
    // // drawline(120, 20, 100, 0, 5);
    // // drawline(300, 300, 350, 350, 6);
    drawLine(300, 305, 350, 355, 7);
    drawLine(300, 297, 350, 347, 7);
    drawLine(300, 300, 350, 350, 15);

    // red through grey
    for (int i = 0; i < 20; i++) {
        drawLine(401 + i, 400, 401 + i, 500, 7);
    }
    drawLine(440, 400, 380, 500, 1);

    // // grey through blue
    for (int i = 0; i < 20; i++) {
        drawLine(461 + i, 400, 461 + i, 500, 2);
    }
    drawLine(440, 400, 500, 500, 7);

    // // red through green
    for (int i = 0; i < 20; i++) {
        drawLine(351 + i, 400, 351 + i, 500, 0);
    }
    drawLine(330, 400, 400, 500, 1);

    endBatching();

    getch();
    setvideomode(3);
    
    end();

    exit();
}
