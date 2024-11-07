#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "arena.h"
#include "logic.h"
#include "state.h"

#define VERYDARKBLUE                                                                                         \
    CLITERAL(Color)                                                                                          \
    {                                                                                                        \
        0, 0, 128, 255                                                                                       \
    }

AppState* initState(Arena* arena)
{
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    AppState* state = allocate(arena, sizeof(AppState));

    // color
    {
        state->color.background = VERYDARKBLUE;
        state->color.foreground = LIGHTGRAY;
        state->color.foregroundHighlight = VERYDARKBLUE;
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
        state->buffer.length = 1;
        state->buffer.capacity = 100000;
        state->buffer.lines = allocate(arena, sizeof(Line*) * state->buffer.capacity);
        state->buffer.lines[0] = newLine(arena);
        state->buffer.cursorPosition = (Vector2){0, 0};

        state->buffer.statusLine = newLine(arena);
    }

    return state;
}

void run(Arena* arena, AppState* state)
{
    state->grid.numCellCols = GetScreenWidth() / state->grid.cellWidth - 1;
    state->grid.numCellRows = GetScreenHeight() / state->grid.cellHeight;

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

    if (IsKeyPressed(KEY_TAB) || IsKeyPressedRepeat(KEY_TAB))
        insertTab(arena, &state->buffer);

    if (IsKeyPressed(KEY_K) || IsKeyPressedRepeat(KEY_K))
        kill(&state->buffer);

    if (IsKeyPressed(KEY_O))
        kill(&state->buffer);

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        backspace(arena, &state->buffer);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER))
        enter(arena, &state->buffer);

    char c;
    while ((c = GetCharPressed()))
        typeChar(arena, &state->buffer, c);
}

void freeState(AppState* state)
{
    UnloadFont(state->font.font);
}
