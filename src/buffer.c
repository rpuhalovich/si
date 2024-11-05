#include <math.h>

#include "buffer.h"

void moveCursorDown(Buffer* b)
{
    if (b->cursorPosition.y < b->lineCount - 1)
        b->cursorPosition.y++;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline].length;
    b->cursorPosition.x = fmin(b->cursorPosition.x, len);
}

void moveCursorUp(Buffer* b)
{
    if (b->cursorPosition.y > 0)
        b->cursorPosition.y--;

    i32 curline = (i32)b->cursorPosition.y;
    i32 len = b->lines[curline].length;
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
    if (b->cursorPosition.x < b->lines[curline].length)
        b->cursorPosition.x++;
}

void moveCursorBeginningOfLine(Buffer* b)
{
    b->cursorPosition.x = 0;
}

void moveCursorEndOfLine(Buffer* b)
{
    i32 curline = (i32)b->cursorPosition.y;
    b->cursorPosition.x = b->lines[curline].length;
}

void typeChar(Buffer* b, char c)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;

    b->lines[curLine].length++;

    // TODO: use arena
    if (b->lines[curLine].length > b->lines[curLine].capacity) {
        b->lines[curLine].capacity *= 2;
        char* newLine = realloc(b->lines[curLine].line, b->lines[curLine].capacity);
        b->lines[curLine].line = newLine;
    }

    for (int i = b->lines[curLine].length; i > curCol; i--)
        b->lines[curLine].line[i] = b->lines[curLine].line[i - 1];

    b->lines[curLine].line[curCol] = c;
    b->cursorPosition.x++;
}

void backspace(Buffer* b)
{
    i32 curLine = (i32)b->cursorPosition.y;
    i32 curCol = (i32)b->cursorPosition.x;
    i32 lineLen = b->lines[curLine].length;

    if (curCol == 0)
        return;

    for (int i = curCol; i < lineLen; i++)
        b->lines[curLine].line[i - 1] = b->lines[curLine].line[i];

    b->lines[curLine].length--;
    b->cursorPosition.x--;
}
