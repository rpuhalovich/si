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
        state->buffer.lineCount = 1;
        state->buffer.lines = malloc(sizeof(Line));
        state->buffer.lines[0].capacity = 16;
        state->buffer.lines[0].len = 0;
        state->buffer.lines[0].line = malloc(sizeof(char) * state->buffer.lines[0].capacity);

        state->buffer.cursorPosition = (Vector2){0, 0};
    }

    return state;
}

void run(AppState* state)
{
    state->grid.numCellCols = GetScreenWidth() / state->grid.cellWidth;
    state->grid.numCellRows = GetScreenHeight() / state->grid.cellHeight;

    state->buffer.cursorPosition.y = iclamp(state->buffer.cursorPosition.y, 0, state->buffer.lineCount);

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
        moveCursorRight(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_F) || IsKeyPressedRepeat(KEY_F)))
        moveCursorRight(&state->buffer);

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
        moveCursorLeft(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_B) || IsKeyPressedRepeat(KEY_B)))
        moveCursorLeft(&state->buffer);

    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
        moveCursorUp(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_P) || IsKeyPressedRepeat(KEY_P)))
        moveCursorUp(&state->buffer);

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
        moveCursorDown(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N)))
        moveCursorDown(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E))
        moveCursorEndOfLine(&state->buffer);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A))
        moveCursorBeginningOfLine(&state->buffer);

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        backspace(&state->buffer);

    char c;
    while ((c = GetCharPressed())) {
        typeChar(c, &state->buffer);
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font.font);
    for (int i = 0; i < state->buffer.lineCount; i++)
        free(state->buffer.lines[i].line);
    free(state->buffer.lines); // probs need to free each char*?
    free(state);
}
