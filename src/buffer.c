#include <limits.h>
#include <math.h>

#include "appmath.h"
#include "buffer.h"

Buffer* newBuffer(Arena* arena)
{
    return newBufferc(arena, 1000);
}

Buffer* newBufferc(Arena* arena, i32 capacity)
{
    Buffer* b = allocate(arena, sizeof(Buffer));
    b->length = 1;
    b->maxLength = INT_MAX;
    b->capacity = capacity;
    b->lines = allocate(arena, sizeof(Line*) * b->capacity);
    b->lines[0] = newLine(arena);
    b->cursorPosition = (Vector2){0, 0};
    return b;
}

void moveCursorDown(Buffer* b)
{
    if (b->cursorPosition.y < b->length - 1 && b->cursorPosition.y < b->maxLength)
        b->cursorPosition.y++;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline]->length;
    b->cursorPosition.x = fmin(b->cursorPosition.x, len);

    if (b->cursorPosition.y > b->numCellRows - 1 + b->scrollOffset.y && b->cursorPosition.y < b->length)
        b->scrollOffset.y++;
}

void moveCursorUp(Buffer* b)
{
    if (b->cursorPosition.y > 0)
        b->cursorPosition.y--;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline]->length;
    b->cursorPosition.x = fmin(b->cursorPosition.x, len);

    if (b->cursorPosition.y < b->scrollOffset.y)
        b->scrollOffset.y--;
}

void moveCursorLeft(Buffer* b)
{
    if (b->cursorPosition.x > 0)
        b->cursorPosition.x--;

    if (b->cursorPosition.x < b->scrollOffset.x)
        b->scrollOffset.x--;
}

void moveCursorRight(Buffer* b)
{
    i32 curline = (i32)b->cursorPosition.y;
    if (b->cursorPosition.x < b->lines[curline]->length)
        b->cursorPosition.x++;

    if (b->cursorPosition.x > b->numCellCols + b->scrollOffset.x && b->cursorPosition.x <= b->lines[curline]->length)
        b->scrollOffset.x++;
}

void moveCursorBeginningOfLine(Buffer* b)
{
    b->cursorPosition.x = 0;
    b->scrollOffset.x = 0;
}

void moveCursorEndOfLine(Buffer* b)
{
    i32 curline = (i32)b->cursorPosition.y;
    b->cursorPosition.x = b->lines[curline]->length;

    if (b->lines[curline]->length > b->scrollOffset.x + b->numCellCols)
        b->scrollOffset.x = b->lines[curline]->length - b->numCellCols;
}

void insertTab(Arena* arena, Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;
    insertString(arena, b->lines[line], "    ", sizeof(char) * 4, b->cursorPosition.x);
    b->cursorPosition.x += 4;
    b->isDirty = true;
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
        moveCursorLeft(b);
    }

    if (column <= 0 && line > 0) {
        i32 oldlen = b->lines[line - 1]->length;

        insertString(arena, b->lines[line - 1], b->lines[line]->characters, b->lines[line]->length, b->lines[line - 1]->length);

        for (i32 i = line; i < b->length - 1; i++)
            b->lines[i] = b->lines[i + 1];

        b->lines[b->length - 1] = NULL;
        b->length = imin(b->length - 1, 1);

        b->cursorPosition.x = oldlen;
        moveCursorUp(b);
    }

    b->isDirty = true;
}

void killl(Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;

    if (b->lines[line]->length == 0 && b->length > 1) {
        for (i32 i = line; i < b->length - 1; i++)
            b->lines[i] = b->lines[i + 1];

        if (line != b->length - 1) {
            b->lines[b->length] = NULL;
            b->length = imin(b->length - 1, 1);
        }
        return;
    }

    b->lines[line]->length = (i32)b->cursorPosition.x;
    b->isDirty = true;
}

void enter(Arena* arena, Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    if (b->length + 1 > b->maxLength)
        return;

    b->length++;

    for (i32 i = b->length - 1; i > curLine; i--) {
        b->lines[i] = b->lines[i - 1];
    }

    b->lines[curLine + 1] = newLine(arena);

    for (i32 i = curCol, j = 0; i < b->lines[curLine]->length; i++, j++) {
        b->lines[curLine + 1]->length++;

        if (b->lines[curLine + 1]->length > b->lines[curLine + 1]->capacity) {
            b->lines[curLine + 1]->characters =
                reallocate(arena, b->lines[curLine + 1]->characters, b->lines[curLine + 1]->capacity, b->lines[curLine + 1]->capacity * 2);

            b->lines[curLine + 1]->capacity *= 2;
        }

        b->lines[curLine + 1]->characters[j] = b->lines[curLine]->characters[i];
    }

    b->lines[curLine]->length = curCol;

    b->cursorPosition.x = 0;
    moveCursorDown(b);
    moveCursorBeginningOfLine(b);

    b->isDirty = true;
}

void append(Arena* arena, Buffer* b, Line* l)
{
    b->length++;
    if (b->length > b->capacity) {
        b->lines = reallocate(arena, b->lines, b->capacity, b->capacity * 2);
        b->capacity *= 2;
    }
    b->lines[b->length - 1] = l;
}

void typeCharb(Arena* arena, Buffer* b, char c)
{
    Line* l = b->lines[(i32)b->cursorPosition.y];
    typeChar(arena, l, b->cursorPosition.x, c);
    moveCursorRight(b);
    b->isDirty = true;
}

void deletec(Buffer* b)
{
    i32 line = (i32)b->cursorPosition.y;
    i32 col = (i32)b->cursorPosition.x;

    for (i32 i = col + 1; i < b->lines[line]->length; i++)
        b->lines[line]->characters[i - 1] = b->lines[line]->characters[i];

    b->lines[line]->length--;
    b->isDirty = true;
}

void zeroUnusedCapacity(Buffer* b)
{
    for (i32 i = 0; i < b->length; i++) {
        Line* l = b->lines[i];
        for (i32 c = l->length; c < l->capacity; c++)
            l->characters[c] = '\0';
        // memset(l->characters + l->length, '\0', l->capacity - l->length);
    }
}
