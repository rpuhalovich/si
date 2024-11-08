#ifndef LINE_H
#define LINE_H

#include "arena.h"
#include "types.h"

typedef struct {
    char* characters;
    i32 length;
    i32 capacity;
} Line;

Line* newLine(Arena* arena);

Line* newLinec(Arena* arena, i32 capacity);

void clearLine(Line* l);

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column);

void typeChar(Arena* arena, Line* l, i32 column, char c);

#endif // LINE_H
