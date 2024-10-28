#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "draw.h"
#include "state.h"

void draw(State* state)
{
    ClearBackground(BLACK);

    // text
    {
        trl_Font f = state->font;
        Buffer b = state->buffer;

        Vector2 origin = (Vector2) { 0, 0 };
        f32 scaleFactor = state->font.size / state->font.font.baseSize;
        f32 fontSpacing = 1.0f;

        for (i32 r = 0; r < state->buffer.lines; r++) {
            f32 textOffsetY = f.size + f.textLineSpacing;
            i32 length = TextLength(state->buffer.text[r]);

            for (i32 c = 0; c < length; c++) {
                f32 textOffsetX = ((f32)state->font.font.glyphs[r].advanceX * scaleFactor + fontSpacing);
                Vector2 pos = { origin.x + textOffsetX * c, origin.y + textOffsetY * r };

                Color backgroundColor = WHITE;
                if (b.cursorPosition.y == r && b.cursorPosition.x == c) {

                    Rectangle rect = {
                        .x = pos.x,
                        .y = pos.y,
                        .width = textOffsetX,
                        .height = state->font.size
                    };
                    DrawRectangleRec(rect, WHITE);

                    backgroundColor = BLACK;
                }


                i32 codepointByteCount = 0;
                i32 codepoint = GetCodepointNext(&state->buffer.text[r][c], &codepointByteCount);
                DrawTextCodepoint(state->font.font, codepoint, pos, state->font.size, backgroundColor);
            }
        }
    }
}
