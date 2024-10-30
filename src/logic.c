#include <math.h>
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
        state->color.background = BEIGE;
        state->color.foreground = BLACK;
        state->color.foregroundHighlight = BEIGE;
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
        state->buffer.lineCount = 3;
        state->buffer.lines = malloc(sizeof(Line*) * state->buffer.lineCount);
        state->buffer.lines[0].line = "blahblahblah";
        state->buffer.lines[1].line = "foofoofoooooooooo";
        state->buffer.lines[2].line = "testing";

        state->buffer.cursorPosition = (Vector2){0, 0};
    }

    return state;
}

void run(AppState* state)
{
    state->grid.numCellCols = GetScreenWidth() / state->grid.cellWidth;
    state->grid.numCellRows = GetScreenHeight() / state->grid.cellHeight;

    state->buffer.cursorPosition.y = iclamp(state->buffer.cursorPosition.y, 0, state->buffer.lineCount);

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
        i32 curline = (i32)state->buffer.cursorPosition.y;
        i32 len = TextLength(state->buffer.lines[curline].line);

        if (state->buffer.cursorPosition.x < len)
            state->buffer.cursorPosition.x++;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
        if (state->buffer.cursorPosition.x > 0)
            state->buffer.cursorPosition.x--;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
        if (state->buffer.cursorPosition.y > 0)
            state->buffer.cursorPosition.y--;

        i32 curline = (i32)state->buffer.cursorPosition.y;
        i32 len = TextLength(state->buffer.lines[curline].line);
        state->buffer.cursorPosition.x = fmin(state->buffer.cursorPosition.x, len);
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
        if (state->buffer.cursorPosition.y < state->buffer.lineCount - 1)
            state->buffer.cursorPosition.y++;

        i32 curline = (i32)state->buffer.cursorPosition.y;
        i32 len = TextLength(state->buffer.lines[curline].line);
        state->buffer.cursorPosition.x = fmin(state->buffer.cursorPosition.x, len);
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font.font);
    free(state->buffer.lines); // probs need to free each char*?
    free(state);
}
