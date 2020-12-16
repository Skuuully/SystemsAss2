#ifndef BATCHER_H
#define BATCHER_H

// Number of commands that can be stored in the buffer at a time
#define COMMAND_BUFFER_SIZE 100

// Data required for console draw line
struct DrawLineCommand {
    int x0;
    int y0;
    int x1;
    int y1;
    int colour;
};

// Data required for console draw circle
struct DrawCircleCommand {
    int xCenter;
    int yCenter;
    int radius;
    int colour;
};

// Data required for console draw rect
struct DrawRectCommand {
    int xLeft;
    int yTop;
    int width;
    int height;
    int colour;
};

// Stores a type of command
union CommandData {
    struct DrawLineCommand drawLineCommand;
    struct DrawCircleCommand drawCircleCommand;
    struct DrawRectCommand drawRectCommand;
};

// Command has some data as well as its type, the type differentiates between which routine should be used to draw
struct Command {
    union CommandData commandData;
    int unionType;
};

// Available routines that can be used to draw to the console
enum CommandType {
    ct_drawLine, ct_drawCircle, ct_fillCircle, ct_drawRect, ct_fillRect
};

void beginBatching();
void endBatching();
void batchDrawLine(int x0, int y0, int x1, int y1, int colour);
void batchDrawCircle(int xCenter, int yCenter, int radius, int colour, bool fill);
void batchDrawRect(int xLeft, int yTop, int width, int height, int colour, bool fill);

#endif
