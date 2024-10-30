#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"

typedef struct {
    char* line;
    i32 len;
} Line;

// used for logic
typedef struct {
    i32 lineCount;
    Line* lines;
    Vector2 cursorPosition;
} Buffer;

#endif // BUFFER_H
