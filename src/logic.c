#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "arena.h"
#include "file.h"
#include "logic.h"
#include "state.h"

AppState* initState(Arena* arena)
{
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    AppState* state = allocate(arena, sizeof(AppState));

    // color
    {
#if 0
        state->color.background = BLACK;
        state->color.foreground = BEIGE;
        state->color.foregroundHighlight = BLACK;
        state->color.cursor = GRAY;
        state->color.border = BEIGE;
        state->color.statusLineBackground = BEIGE;
        state->color.statusLineForeGround = BLACK;
        state->color.statusLineCursor = GRAY;
#endif
#if 1
        state->color.background = BEIGE;
        state->color.foreground = BLACK;
        state->color.foregroundHighlight = BEIGE;
        state->color.cursor = GRAY;
        state->color.border = BLACK;
        state->color.statusLineBackground = BLACK;
        state->color.statusLineForeGround = BEIGE;
        state->color.statusLineCursor = GRAY;
#endif
    }

    // TODO: https://rodneylab.com/raylib-sdf-fonts/
    // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
    // font
    {
        state->font = allocate(arena, sizeof(AppFont));
        state->font->font = LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 32, 0, 250);
        state->font->size = state->font->font.baseSize / 2;
        state->font->spacing = 1.0f;
        state->font->textLineSpacing = 2;

        Vector2 monospaceCharDimensions = MeasureTextEx(state->font->font, "x", state->font->size, 1.0f);
        state->font->charWidth = monospaceCharDimensions.x;
        state->font->charHeight = monospaceCharDimensions.y;
    }

    char* path = "/Users/rp/Desktop/tmp/.vimrc";
    Buffer* b = load(arena, newLines(arena, path));
    if (b == NULL)
        b = newBuffer(arena);
    state->currentBuffer.buffer = b;
    state->currentBuffer.buffer->isActive = true;
    state->currentBuffer.fileName = newLine(arena);
    insertString(arena, state->currentBuffer.fileName, path, strlen(path), 0);

    state->statusLine.commandLine.commandLineInput = newBuffer(arena);

    return state;
}

void run(Arena* arena, AppState* state)
{
    state->statusLine.bounds.x = 0;
    state->statusLine.bounds.y = GetScreenHeight() - state->font->charHeight - 8;
    state->statusLine.bounds.width = GetScreenWidth();
    state->statusLine.bounds.height = state->font->charHeight;

    state->currentBuffer.buffer->bounds = RectangleWiden(
        (Rectangle){
            .x = 0,
            .y = 0,
            .width = GetScreenWidth(),
            .height = GetScreenHeight() - state->font->charHeight - 8},
        -16.f);

    state->currentBuffer.buffer->numCellCols =
        state->currentBuffer.buffer->bounds.width / state->font->charWidth - 1;
    state->currentBuffer.buffer->numCellRows =
        state->currentBuffer.buffer->bounds.height / state->font->charHeight - 1;

    Buffer* b;
    if (state->currentMode == EDIT)
        b = state->currentBuffer.buffer;
    if (state->currentMode == OPEN_FILE)
        b = state->statusLine.commandLine.commandLineInput;

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
        moveCursorRight(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_F) || IsKeyPressedRepeat(KEY_F)))
        moveCursorRight(b);

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
        moveCursorLeft(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_B) || IsKeyPressedRepeat(KEY_B)))
        moveCursorLeft(b);

    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
        moveCursorUp(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_P) || IsKeyPressedRepeat(KEY_P)))
        moveCursorUp(b);

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
        moveCursorDown(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N)))
        moveCursorDown(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E))
        moveCursorEndOfLine(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A))
        moveCursorBeginningOfLine(b);

    if (IsKeyPressed(KEY_TAB) || IsKeyPressedRepeat(KEY_TAB))
        insertTab(arena, state->currentBuffer.buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_K) || IsKeyPressedRepeat(KEY_K))
        kill(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
        clearLine(state->statusLine.commandLine.commandLineInput->lines[0]);
        state->statusLine.commandLine.commandLineInput->cursorPosition.x = 0;
        state->currentMode = OPEN_FILE;
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        backspace(arena, b);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER)) {
        if (state->currentMode == EDIT)
            enter(arena, b);
    }

    char c;
    while ((c = GetCharPressed()))
        typeCharb(arena, b, c);

    if (state->currentMode == OPEN_FILE) {
        if (IsKeyPressed(KEY_ENTER)) {
            state->currentMode = EDIT;
        }
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font->font);
}
