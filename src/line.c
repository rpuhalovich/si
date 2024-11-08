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

Line* newLines(Arena* arena, char* str)
{
    i32 len = strlen(str);
    i32 capacity = 1;
    while (len > capacity)
        capacity *= 2;
    Line* l = newLinec(arena, capacity);
    l->length = len;
    memcpy(l->characters, str, len);
    return l;
}

Line* newLinel(Arena* arena, Line* l)
{
    Line* newl = newLinec(arena, l->capacity);
    newl->length = l->length;
    memcpy(newl->characters, l->characters, l->length);
    return newl;
}

void clearLine(Line* l)
{
    memset(l->characters, 0, l->capacity);
    l->length = 0;
}

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column)
{
    i32 cutLen = l->length - column;

    i32 originalCapacity = l->capacity;
    l->length = l->length + strlen;
    while (l->length > l->capacity)
        l->capacity *= 2;

    if (originalCapacity < l->capacity)
        l->characters = reallocate(arena, l->characters, l->capacity, l->capacity);

    memcpy(l->characters + column + strlen, l->characters + column, cutLen);
    memcpy(l->characters + column, str, strlen);
}

void typeChar(Arena* arena, Line* l, i32 column, char c)
{
    l->length++;

    if (l->length > l->capacity) {
        l->characters = reallocate(arena, l->characters, l->capacity, l->capacity * 2);
        l->capacity *= 2;
    }

    for (i32 i = l->length - 1; i > column; i--)
        l->characters[i] = l->characters[i - 1];

    l->characters[column] = c;
}
