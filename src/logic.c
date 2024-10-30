#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "logic.h"
#include "state.h"

AppState* init()
{
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    AppState* state = malloc(sizeof(AppState));
    memset(state, 0, sizeof(AppState));

    // color
    {
        state->color.background = BLACK;
        state->color.foreground = WHITE;
        state->color.foregroundHighlight = BLACK;
    }

    // font
    {
        // TODO: https://rodneylab.com/raylib-sdf-fonts/
        // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
        state->font.font = LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 32, 0, 250);
        state->font.size = state->font.font.baseSize / 2;
        state->font.spacing = 1.0f;
        state->font.textLineSpacing = 2;

        // cell dimensions
        f32 scaleFactor = state->font.size / state->font.font.baseSize;
        Vector2 monospaceCharDimensions = MeasureTextEx(state->font.font, "x", state->font.size, 1.0f);

        state->grid.cellWidth = monospaceCharDimensions.x;
        state->grid.cellHeight = state->font.size + state->font.textLineSpacing;
    }

    // buffer
    {
        state->buffer.lines = 3;
        state->buffer.text = malloc(sizeof(char*) * state->buffer.lines);
        state->buffer.text[0] = "blahblahblah";
        state->buffer.text[1] = "foofoofoooooooooo";
        state->buffer.text[2] = "testing";

        state->buffer.cursorPosition = (Vector2){0, 0};
    }

    return state;
}

void run(AppState* state)
{
    state->grid.numCellCols = GetScreenWidth() / state->grid.cellWidth;
    state->grid.numCellRows = GetScreenHeight() / state->grid.cellHeight;

    state->buffer.cursorPosition.x = iclamp(state->buffer.cursorPosition.x, 0, state->grid.numCellCols - 1);
    state->buffer.cursorPosition.y = iclamp(state->buffer.cursorPosition.y, 0, state->grid.numCellRows - 1);

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
        bool isInWindow = state->buffer.cursorPosition.x < state->grid.numCellCols - 1;
        bool isInLine = state->buffer.cursorPosition.x < state->grid.numCellCols - 1;
        if (isInWindow || isInLine)
            state->buffer.cursorPosition.x++;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
        if (state->buffer.cursorPosition.x > 0)
            state->buffer.cursorPosition.x--;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
        if (state->buffer.cursorPosition.y > 0)
            state->buffer.cursorPosition.y--;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
        if (state->buffer.cursorPosition.y < state->grid.numCellRows - 1)
            state->buffer.cursorPosition.y++;
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font.font);
    free(state->buffer.text);
    free(state);
}
