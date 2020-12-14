#include "types.h"
#include "user.h"

int main() {
    begin();

    setvideomode(0x12);

    drawline(100, 100, 200, 200, 0);
    drawline(0, 0, 0, 20, 1);
    drawline(0, 0, 100, 100, 2);
    drawline(10, 0, 30, 0, 3);
    drawline(100, 100, 120, 20, 4);
    drawline(120, 20, 100, 0, 5);
    drawline(300, 300, 350, 350, 6);
    drawline(300, 305, 350, 355, 7);
    drawline(300, 297, 350, 347, 7);
    //drawline(300, 300, 350, 350, 15);
    for (int i = 0; i < 20; i++) {
        drawline(20 + i, 20, 20 + i, 100, 10);
        drawline(20 - i, 20, 20 - i, 100, 2);
    }

    // red through grey
    for (int i = 0; i < 20; i++) {
        drawline(401 + i, 400, 401 + i, 500, 7);
    }
    drawline(440, 400, 380, 500, 1);

    // grey through blue
    for (int i = 0; i < 20; i++) {
        drawline(461 + i, 400, 461 + i, 500, 2);
    }
    drawline(440, 400, 500, 500, 7);

    // red through green
    for (int i = 0; i < 20; i++) {
        drawline(351 + i, 400, 351 + i, 500, 0);
    }
    drawline(330, 400, 400, 500, 1);

    getch();
    setvideomode(3);
    
    end();

    exit();
}
