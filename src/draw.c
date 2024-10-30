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
        Buffer b = state->buffer;

        for (i32 r = 0; r < state->grid.numCellRows; r++) {
            i32 rowLen;
            if (r < state->buffer.lineCount)
                rowLen = TextLength(state->buffer.lines[r].line);

            for (i32 c = 0; c < state->grid.numCellCols; c++) {
                Vector2 pos = {c * state->grid.cellWidth, r * state->grid.cellHeight};
                Color color = state->color.foreground;
                if (b.cursorPosition.y == r && b.cursorPosition.x == c) {
                    Rectangle rect = {
                        .x = pos.x,
                        .y = pos.y,
                        .width = state->grid.cellWidth,
                        .height = state->grid.cellHeight};
                    DrawRectangleRec(rect, state->color.foreground);
                    color = state->color.foregroundHighlight;
                }

                // cursor assumed not to go below { 0, 0 }
                if (r < state->buffer.lineCount && c < rowLen) {
                    i32 codepointByteCount = 0;
                    char character = state->buffer.lines[r].line[c];
                    i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
                    DrawTextCodepoint(state->font.font, codepoint, pos, state->font.size, color);
                }
            }
        }
    }
}
