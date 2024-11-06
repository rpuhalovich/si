#ifndef BUFFER_H
#define BUFFER_H

#include <raylib.h>

#include "types.h"

typedef struct {
    char* characters;
    i32 length;
    i32 capacity;
} Line;

typedef struct {
    Line* lines;
    i32 length;
    i32 capacity;

    Vector2 cursorPosition;
} Buffer;

void moveCursorUp(Buffer* b);
void moveCursorDown(Buffer* b);
void moveCursorLeft(Buffer* b);
void moveCursorRight(Buffer* b);
void moveCursorBeginningOfLine(Buffer* b);
void moveCursorEndOfLine(Buffer* b);

void typeChar(Buffer* b, char c);
void backspace(Buffer* b);
void cutToEnd(Buffer* b);
void enter(Buffer* b);

#endif // BUFFER_H
