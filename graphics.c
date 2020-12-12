#include "types.h"
#include "user.h"

void clearScreen();

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
    drawline(300, 300, 350, 350, 8);

    getch();
    setvideomode(3);
    
    end();

    exit();
}

void clearScreen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 200; y++) {
            setpixel(x, y, 0);
        }
    }
}
