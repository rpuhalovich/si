#ifndef LINE_H
#define LINE_H

#include "arena.h"
#include "types.h"

// TODO: this should probably be renamed to String

typedef struct {
    char* characters;
    i32 length;
    i32 capacity;
} Line;

Line* newLine(Arena* arena);

Line* newLinec(Arena* arena, i32 capacity);

Line* newLines(Arena* arena, char* str);

Line* newLinel(Arena* arena, Line* l);

void clearLine(Line* l);

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column);

void typeChar(Arena* arena, Line* l, i32 column, char c);

#endif // LINE_H
