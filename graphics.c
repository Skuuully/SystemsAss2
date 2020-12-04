#include "types.h"
#include "user.h"

void testFunc();

int main() {
    setvideomode(0x13);

    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 200; y++) {
            setpixel(x, y, 0);
        }
    }

    drawline(0, 0, 100, 100, 15);
    drawline(10, 0, 30, 0, 15);
    drawline(100, 100, 120, 20, 15);
    drawline(120, 20, 100, 0, 15);

    getch();
    exit();
}

void testFunc() {
    printf(1, "I was called correctly\n");
}
