
#ifndef BATCHER_H
#define BATCHER_H

// Number of commands that can be stored in the buffer at a time
#define COMMAND_BUFFER_SIZE 100

struct DrawLineCommand {
    int x0;
    int y0;
    int x1;
    int y1;
    int colour;
};

struct DrawCircleCommand {
    int xCenter;
    int yCenter;
    int radius;
    int colour;
};

union CommandData {
    struct DrawLineCommand drawLineCommand;
    struct DrawCircleCommand drawCircleCommand;
};

struct Command {
    union CommandData commandData;
    int unionType;
};

enum CommandType {
    ct_drawLine, ct_drawCircle
};

void beginBatching();
void endBatching();
void batchDrawLine(int x0, int y0, int x1, int y1, int colour);
void batchDrawCircle(int xCenter, int yCenter, int radius, int colour);

#endif
