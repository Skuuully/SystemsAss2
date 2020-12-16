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

struct DrawRectCommand {
    int xLeft;
    int yTop;
    int width;
    int height;
    int colour;
};

union CommandData {
    struct DrawLineCommand drawLineCommand;
    struct DrawCircleCommand drawCircleCommand;
    struct DrawRectCommand drawRectCommand;
};

struct Command {
    union CommandData commandData;
    int unionType;
};

enum CommandType {
    ct_drawLine, ct_drawCircle, ct_fillCircle, ct_drawRect, ct_fillRect
};

void beginBatching();
void endBatching();
void AddCommand(union CommandData commandData, int commandType);
void batchDrawLine(int x0, int y0, int x1, int y1, int colour);
void batchDrawCircle(int xCenter, int yCenter, int radius, int colour, bool fill);
void batchDrawRect(int xLeft, int yTop, int width, int height, int colour, bool fill);

#endif
