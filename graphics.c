#include "types.h"
#include "user.h"
#include "batcher.h"

int main() {
    setvideomode(0x12);
    beginBatching();

    for (int i = 0; i < 16; i++) {
        batchDrawRect(20 + (i * 20), 0, 20, 180, i, true);
        batchDrawRect(25 + (i * 20), 0, 10, 80, 15 - i, false);

        batchDrawCircle(240, 220, 50 - (i * 3), i, false);
        batchDrawCircle(340, 420, 50 - (i * 3), 16 - i, true);

        batchDrawLine(0, i * 10, 639, 479 - (i * 10), i);
        batchDrawLine(639, i * 10, 0, 479 - (i * 10), i);

        batchDrawPixel(50 + i, 200, i);
    }

    for (int i = 0; i < 9; i++) {
        batchDrawLine(0, 236 + i, 640, 236 + i, i);
    }

    endBatching();

    getch();
    setvideomode(3);
    exit();
}
