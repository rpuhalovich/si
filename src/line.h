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

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column);

#endif // LINE_H
