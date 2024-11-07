#include <math.h>

#include "buffer.h"

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

void typeChar(Buffer* b, char c)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    b->lines[curLine]->length++;

    // TODO: use arena
    if (b->lines[curLine]->length > b->lines[curLine]->capacity) {
        b->lines[curLine]->capacity *= 2;
        char* newLine = realloc(b->lines[curLine]->characters, b->lines[curLine]->capacity);
        b->lines[curLine]->characters = newLine;
    }

    for (int i = b->lines[curLine]->length - 1; i > curCol; i--)
        b->lines[curLine]->characters[i] = b->lines[curLine]->characters[i - 1];

    b->lines[curLine]->characters[curCol] = c;
    b->cursorPosition.x++;
}

void backspace(Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;
    i32 lineLen = b->lines[curLine]->length;

    if (curCol == 0)
        return;

    for (int i = curCol; i < lineLen; i++)
        b->lines[curLine]->characters[i - 1] = b->lines[curLine]->characters[i];

    b->lines[curLine]->length--;
    b->cursorPosition.x--;
}

void kill(Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    b->lines[curLine]->length = (i32)b->cursorPosition.x;
}

void enter(Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    b->length++;

    // TODO: use arena
    if (b->length > b->capacity) {
        b->capacity *= 2;
        Line** newLines = realloc(b->lines, b->capacity);
        b->lines = newLines;
    }

    for (i32 i = b->length - 1; i > curLine; i--) {
        b->lines[i] = b->lines[i - 1];
    }

    b->lines[curLine] = newLine();

    int curChar = 0;
    for (i32 i = curCol; i < b->lines[curLine]->length; i++) {
        b->lines[curLine + 1]->length++;

        if (b->lines[curLine + 1]->length > b->lines[curLine + 1]->capacity) {
            b->lines[curLine + 1]->capacity *= 2;
            char* newLine = realloc(b->lines[curLine + 1]->characters, b->lines[curLine + 1]->capacity);
            b->lines[curLine + 1]->characters = newLine;
        }

        b->lines[curLine + 1]->characters[curChar] = b->lines[curLine]->characters[i];
    }

    b->cursorPosition.x = 0;
    b->cursorPosition.y++;
}

Line* newLine()
{
    Line* l = malloc(sizeof(Line));
    l->length = 0;
    l->capacity = 16;
    l->characters = malloc(sizeof(char) * l->capacity);
    return l;
}

void freeLine(Line* l)
{
    free(l->characters);
    free(l);
}
