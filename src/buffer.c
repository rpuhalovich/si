#include <math.h>

#include "appmath.h"
#include "buffer.h"

void insertString(Arena* arena, Line* l, char* str, u32 strlen, i32 column);

void moveCursorDown(Buffer* b)
{
    if (b->cursorPosition.y < b->length - 1)
        b->cursorPosition.y++;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline]->length;
    b->cursorPosition.x = fmin(b->cursorPosition.x, len);
}

void moveCursorUp(Buffer* b)
{
    if (b->cursorPosition.y > 0)
        b->cursorPosition.y--;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline]->length;
    b->cursorPosition.x = fmin(b->cursorPosition.x, len);
}

void moveCursorLeft(Buffer* b)
{
    if (b->cursorPosition.x > 0)
        b->cursorPosition.x--;
}

void moveCursorRight(Buffer* b)
{
    i32 curline = (i32)b->cursorPosition.y;
    if (b->cursorPosition.x < b->lines[curline]->length)
        b->cursorPosition.x++;
}

void moveCursorBeginningOfLine(Buffer* b)
{
    b->cursorPosition.x = 0;
}

void moveCursorEndOfLine(Buffer* b)
{
    i32 curline = (i32)b->cursorPosition.y;
    b->cursorPosition.x = b->lines[curline]->length;
}

void typeChar(Arena* arena, Buffer* b, char c)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    b->lines[curLine]->length++;

    // TODO: use arena
    if (b->lines[curLine]->length > b->lines[curLine]->capacity) {
        b->lines[curLine]->characters = reallocate(
            arena,
            b->lines[curLine]->characters,
            b->lines[curLine]->capacity,
            b->lines[curLine]->capacity * 2);

        b->lines[curLine]->capacity *= 2;
    }

    for (i32 i = b->lines[curLine]->length - 1; i > curCol; i--)
        b->lines[curLine]->characters[i] = b->lines[curLine]->characters[i - 1];

    b->lines[curLine]->characters[curCol] = c;
    b->cursorPosition.x++;
}

void insertTab(Arena* arena, Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;
    insertString(arena, b->lines[line], "    ", sizeof(char) * 4, b->cursorPosition.x);
    b->cursorPosition.x += 4;
}

void backspace(Arena* arena, Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;
    i32 column = (i32)b->cursorPosition.x;
    i32 lineLen = b->lines[line]->length;

    if (column > 0) {
        for (i32 i = column; i < lineLen; i++)
            b->lines[line]->characters[i - 1] = b->lines[line]->characters[i];

        b->lines[line]->length--;
        b->cursorPosition.x--;
    }

    if (column <= 0 && line > 0) {
        i32 oldlen = b->lines[line - 1]->length;

        insertString(
            arena,
            b->lines[line - 1],
            b->lines[line]->characters,
            b->lines[line]->length,
            b->lines[line - 1]->length);

        for (i32 i = line; i < b->length - 1; i++)
            b->lines[i] = b->lines[i + 1];

        b->lines[b->length - 1] = NULL;
        b->length = imin(b->length - 1, 1);

        b->cursorPosition.x = oldlen;
        b->cursorPosition.y--;
    }
}

void kill(Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;

    if (b->lines[line]->length == 0 && b->length > 1) {
        for (i32 i = line; i < b->length - 1; i++)
            b->lines[i] = b->lines[i + 1];
        b->lines[b->length] = NULL;
        b->length = imin(b->length - 1, 1);
        return;
    }

    b->lines[line]->length = (i32)b->cursorPosition.x;
}

void enter(Arena* arena, Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    b->length++;

    for (i32 i = b->length - 1; i > curLine; i--) {
        b->lines[i] = b->lines[i - 1];
    }

    b->lines[curLine + 1] = newLine(arena);

    for (i32 i = curCol, j = 0; i < b->lines[curLine]->length; i++, j++) {
        b->lines[curLine + 1]->length++;

        if (b->lines[curLine + 1]->length > b->lines[curLine + 1]->capacity) {
            b->lines[curLine + 1]->characters = reallocate(
                arena,
                b->lines[curLine + 1]->characters,
                b->lines[curLine + 1]->capacity,
                b->lines[curLine + 1]->capacity * 2);

            b->lines[curLine + 1]->capacity *= 2;
        }

        b->lines[curLine + 1]->characters[j] = b->lines[curLine]->characters[i];
    }

    b->lines[curLine]->length = curCol;

    b->cursorPosition.x = 0;
    b->cursorPosition.y++;
}

Line* newLine(Arena* arena)
{
    Line* l = allocate(arena, sizeof(Line));
    memset(l, 0, sizeof(Line));
    l->length = 0;
    l->capacity = 16;
    l->characters = allocate(arena, sizeof(char) * l->capacity);
    memset(l->characters, 0, sizeof(char) * l->capacity);
    return l;
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
