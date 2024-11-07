#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "draw.h"
#include "state.h"

void draw(AppState* state)
{
    ClearBackground(state->color.background);

    // grid
    {
        i32 firstOutOfBoundsXRight = state->grid.gridXOffset + state->grid.numCellCols;
        if (state->buffer.cursorPosition.x > firstOutOfBoundsXRight) {
            state->grid.gridXOffset += state->buffer.cursorPosition.x - firstOutOfBoundsXRight;
        }

        if (state->buffer.cursorPosition.x < state->grid.gridXOffset) {
            state->grid.gridXOffset = state->buffer.cursorPosition.x;
        }

        for (i32 r = 0; r < state->grid.numCellRows - 1; r++) {
            i32 gridOffset = state->grid.numCellCols + state->grid.gridXOffset + 1;
            for (i32 c = state->grid.gridXOffset; c < gridOffset; c++) {
                Vector2 pos = {
                    (c - state->grid.gridXOffset) * state->grid.cellWidth, r * state->grid.cellHeight};
                Color color = state->color.foreground;

                if (state->buffer.cursorPosition.y == r && state->buffer.cursorPosition.x == c) {
                    Rectangle rect = {
                        .x = pos.x,
                        .y = pos.y,
                        .width = state->grid.cellWidth,
                        .height = state->grid.cellHeight};
                    DrawRectangleRec(rect, state->color.foreground);
                    color = state->color.foregroundHighlight;
                }

                if (r < state->buffer.length && c < state->buffer.lines[r]->length) {
                    i32 codepointByteCount = 0;
                    char character = state->buffer.lines[r]->characters[c];
                    i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
                    DrawTextCodepoint(state->font.font, codepoint, pos, state->font.size, color);
                }
            }
        }
    }

    // status line
    {
        Vector2 pos = {0, GetScreenHeight() - state->grid.cellHeight};

        Rectangle rect = {
            .x = pos.x, .y = pos.y, .width = GetScreenWidth(), .height = state->grid.cellHeight};
        DrawRectangleRec(rect, state->color.foreground);

        char* hello = "~/dev/test-raylib/src/draw.c [+]";
        for (i32 i = 0; i < strlen(hello); i++) {
            i32 codepointByteCount = 0;
            char character = hello[i];
            i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
            DrawTextCodepoint(
                state->font.font, codepoint, pos, state->font.size, state->color.foregroundHighlight);
            pos.x += state->grid.cellWidth;
        }
    }
}
