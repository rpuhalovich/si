#ifndef BUFFER_H
#define BUFFER_H

#include <raylib.h>

#include "arena.h"
#include "types.h"

typedef enum {
    EDIT,
    COMMAND
} Mode;

typedef struct {
    char* characters;
    i32 length;
    i32 capacity;
} Line;

typedef struct {
    Line** lines;
    i32 length;
    i32 capacity;

    Vector2 cursorPosition;

    bool isDirty;
    Line* fileName;
    Mode currentMode;
} Buffer;

void moveCursorUp(Buffer* b);
void moveCursorDown(Buffer* b);
void moveCursorLeft(Buffer* b);
void moveCursorRight(Buffer* b);
void moveCursorBeginningOfLine(Buffer* b);
void moveCursorEndOfLine(Buffer* b);

void typeChar(Arena* arena, Line* l, i32 column, char c);
void insertTab(Arena* arena, Buffer* b);

void backspace(Arena* arena, Buffer* b);
void kill(Buffer* b);
void enter(Arena* arena, Buffer* b);

Line* newLine(Arena* arena);

#endif // BUFFER_H
