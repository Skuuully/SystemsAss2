#include "types.h"
#include "user.h"

void clearScreen();

int main() {
    begin();
    setvideomode(0x13);

    clearScreen();

    drawline(0, 0, 100, 100, 15);
    drawline(10, 0, 30, 0, 15);
    drawline(100, 100, 120, 20, 15);
    drawline(120, 20, 100, 0, 15);

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
