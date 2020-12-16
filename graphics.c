#include "types.h"
#include "user.h"
#include "batcher.h"

int main() {
    setvideomode(0x12);
    beginBatching();

    int off = 20;
    for (int i = off; i < off + 20; i++) {
        for (int j = 0; j < 16; j++) {
            batchDrawLine(0 + i + (j * off), 0, 0 + i + (j * off), 200, j);
        }
    }

    for (int i = 0; i < 16; i++) {
        batchDrawLine(0, 20 + (i * 3), 640, 20 + (i * 3), i);
    }

    batchDrawLine(300, 305, 350, 355, 7);
    batchDrawLine(300, 297, 350, 347, 7);
    batchDrawLine(300, 300, 350, 350, 15);

    // red through grey
    for (int i = 0; i < 20; i++) {
        batchDrawLine(401 + i, 400, 401 + i, 500, 7);
    }
    batchDrawLine(440, 400, 380, 500, 1);

    // grey through blue
    for (int i = 0; i < 20; i++) {
        batchDrawLine(461 + i, 400, 461 + i, 500, 2);
    }
    batchDrawLine(440, 400, 500, 500, 7);

    // red through green
    for (int i = 0; i < 20; i++) {
        batchDrawLine(351 + i, 400, 351 + i, 500, 0);
    }
    batchDrawLine(330, 400, 400, 500, 1);

    batchDrawCircle(100, 400, 50, 4, true);
    batchDrawCircle(100, 400, 50, 0, false);

    // batchDrawRect(20, 100, 30, 40, 12, false);

    endBatching();

    getch();
    setvideomode(3);
    exit();
}
