#include "line.h"

Line* newLinec(Arena* arena, i32 capacity)
{
    Line* l = allocate(arena, sizeof(Line));
    memset(l, 0, sizeof(Line));
    l->length = 0;
    l->capacity = capacity;
    l->characters = allocate(arena, sizeof(char) * l->capacity);
    memset(l->characters, 0, sizeof(char) * l->capacity);
    return l;
}

Line* newLine(Arena* arena)
{
    return newLinec(arena, 16);
}

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column)
{
    i32 cutLen = l->length - column;

    l->length = l->length + strlen;
    while (l->length > l->capacity) {
        l->characters = reallocate(arena, l->characters, l->capacity, l->capacity * 2);
        l->capacity *= 2;
    }

    memcpy(l->characters + column + strlen, l->characters + column, cutLen);
    memcpy(l->characters + column, str, strlen);
}
