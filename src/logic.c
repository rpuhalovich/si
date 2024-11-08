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
        state->color.background = BEIGE;
        state->color.foreground = BLACK;
        state->color.foregroundHighlight = BEIGE;
    }

    // font
    {
        // TODO: https://rodneylab.com/raylib-sdf-fonts/
        // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering

        state->font = allocate(arena, sizeof(AppFont));
        state->font->font = LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 32, 0, 250);
        state->font->size = state->font->font.baseSize / 2;
        state->font->spacing = 1.0f;
        state->font->textLineSpacing = 2;

        Vector2 monospaceCharDimensions = MeasureTextEx(state->font->font, "x", state->font->size, 1.0f);
        state->font->charWidth = monospaceCharDimensions.x;
        state->font->charHeight = monospaceCharDimensions.y;
        state->grid.cellWidth = monospaceCharDimensions.x;
        state->grid.cellHeight = state->font->size + state->font->textLineSpacing;
    }

    // state->buffer = newBuffer(arena);

    Buffer* b = load(arena, newLines(arena, "/Users/rp/Desktop/tmp/.vimrc"));
    if (b == NULL)
        b = newBuffer(arena);
    state->buffer = b;
    state->buffer->bounds.x = 100;
    state->buffer->bounds.y = 100;
    state->buffer->bounds.width = 600;
    state->buffer->bounds.height = 400;

    b->numCellCols = b->bounds.width / state->font->charWidth - 1;
    b->numCellRows = b->bounds.height / state->font->charHeight - 1;

    state->commandLine.tempFileName = newBuffer(arena);
    state->commandLine.tempFileName->maxLength = 1;

    char* tmpstr = "hello there";
    state->file.fileName = newLines(arena, tmpstr);

    return state;
}

void run(Arena* arena, AppState* state)
{
    state->grid.numCellCols = GetScreenWidth() / state->grid.cellWidth - 1;
    state->grid.numCellRows = GetScreenHeight() / state->grid.cellHeight;

    Buffer* b;
    if (state->currentMode == EDIT)
        b = state->buffer;
    if (state->currentMode == OPEN_FILE)
        b = state->commandLine.tempFileName;

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
        insertTab(arena, state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_K) || IsKeyPressedRepeat(KEY_K))
        kill(b);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
        clearLine(state->commandLine.tempFileName->lines[0]);

        // char* openFileDialog = "file: ";
        // insertString(
        //     arena,
        //     state->commandLine.tempFileName->lines[0],
        //     openFileDialog,
        //     sizeof(char) * strlen(openFileDialog),
        //     0);

        state->commandLine.tempFileName->cursorPosition.x = state->commandLine.tempFileName->lines[0]->length;

        state->currentMode = OPEN_FILE;
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        backspace(arena, b);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER))
        enter(arena, state->buffer);

    if (state->currentMode == EDIT) {
        char c;
        while ((c = GetCharPressed())) {
            Line* l = state->buffer->lines[(i32)state->buffer->cursorPosition.y];
            typeChar(arena, l, state->buffer->cursorPosition.x, c);
            state->buffer->cursorPosition.x++;
        }
    }

    if (state->currentMode == OPEN_FILE) {
        if (IsKeyPressed(KEY_ENTER)) {
            state->currentMode = EDIT;
        }

        char c;
        while ((c = GetCharPressed())) {
            Line* l = state->commandLine.tempFileName->lines[0];
            typeChar(arena, l, state->commandLine.tempFileName->lines[0]->length, c);
            state->commandLine.tempFileName->cursorPosition.x++;
        }
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font->font);
}
