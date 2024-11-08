#ifndef BUFFER_H
#define BUFFER_H

#include <raylib.h>

#include "arena.h"
#include "line.h"
#include "types.h"

typedef struct {
    Line** lines;
    i32 length;
    i32 maxLength;
    i32 capacity;

    Vector2 cursorPosition;
    Vector2 scrollOffset;
    i32 numCols;
    i32 numRows;

    bool isActive;
    Rectangle bounds;
} Buffer;

Buffer* newBuffer(Arena* arena);

Buffer* newBufferc(Arena* arena, i32 capacity);

void moveCursorUp(Buffer* b);

void moveCursorDown(Buffer* b);

void moveCursorLeft(Buffer* b);

void moveCursorRight(Buffer* b);

void moveCursorBeginningOfLine(Buffer* b);

void moveCursorEndOfLine(Buffer* b);

void insertTab(Arena* arena, Buffer* b);

void kill(Buffer* b);

void enter(Arena* arena, Buffer* b);

void backspace(Arena* arena, Buffer* b);

void append(Arena* arena, Buffer* b, Line* l);

#endif // BUFFER_H
