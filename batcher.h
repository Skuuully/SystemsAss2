
#ifndef BATCHER_H
#define BATCHER_H

// Number of commands that can be stored in the buffer at a time
#define COMMAND_BUFFER_SIZE 100

struct Command {
    int x0;
    int y0;
    int x1;
    int y1;
    int colour;
};

void beginBatching();
void endBatching();
void batchDrawLine(int x0, int y0, int x1, int y1, int colour);

#endif
