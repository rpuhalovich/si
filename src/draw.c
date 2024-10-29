#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "draw.h"
#include "state.h"

void draw(trl_State* state)
{
    ClearBackground(BLACK);

    // grid
    {
        trl_Font f = state->font;
        Buffer b = state->buffer;
        f32 scaleFactor = state->font.size / state->font.font.baseSize;
        Vector2 monospaceCharDimensions = MeasureTextEx(state->font.font, "x", state->font.size, 1.0f);

        f32 cellWidth = monospaceCharDimensions.x;
        f32 cellHeight = f.size + f.textLineSpacing;

        i32 numCellCols = GetRenderWidth() / cellWidth;
        i32 numCellRows = GetRenderHeight() / cellHeight;

        for (i32 r = 0; r < numCellRows; r++) {
            i32 rowLen;
            if (r < state->buffer.lines)
                rowLen = TextLength(state->buffer.text[r]);

            for (i32 c = 0; c < numCellCols; c++) {
                Vector2 pos = {c * cellWidth, r * cellHeight};
                Color color = WHITE;
                if (b.cursorPosition.y == r && b.cursorPosition.x == c) {
                    Rectangle rect = {.x = pos.x, .y = pos.y, .width = cellWidth, .height = cellHeight};
                    DrawRectangleRec(rect, WHITE);
                    color = BLACK;
                }

                // cursor assumed not to go below { 0, 0 }
                if (r < state->buffer.lines && c < rowLen) {
                    i32 codepointByteCount = 0;
                    char character = state->buffer.text[r][c];
                    i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
                    DrawTextCodepoint(state->font.font, codepoint, pos, state->font.size, color);
                }
            }
        }
    }
}
