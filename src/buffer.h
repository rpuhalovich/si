#ifndef BUFFER_H
#define BUFFER_H

#include <raylib.h>

#include "types.h"

typedef struct {
    char* line;
    i32 length;
    i32 capacity;
} Line;

// used for logic
typedef struct {
    i32 lineCount;
    Line* lines;
    Vector2 cursorPosition;
} Buffer;

void moveCursorUp(Buffer* b);
void moveCursorDown(Buffer* b);
void moveCursorLeft(Buffer* b);
void moveCursorRight(Buffer* b);

void moveCursorBeginningOfLine(Buffer* b);
void moveCursorEndOfLine(Buffer* b);

void typeChar(char c, Buffer* b);
void backspace(Buffer* b);

#endif // BUFFER_H
