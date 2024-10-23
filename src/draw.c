#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "draw.h"
#include "state.h"

void draw(State* state)
{
    ClearBackground(BLACK);

    // font
    {
        Vector2 position = (Vector2){0, 0};
        f32 fontSize = state->font.size;
        f32 fontBaseSize = state->font.font.baseSize;
        f32 fontSpacing = 1.0f;
        i32 textLineSpacing = state->font.textLineSpacing;

        for (i32 r = 0; r < state->buffer.lines; r++) {
            f32 textOffsetY = fontSize + state->font.textLineSpacing;

            Vector2 pos = { 0, (fontSize + state->font.textLineSpacing) * r };

            if (state->font.font.texture.id == 0)
                state->font.font = GetFontDefault();

            i32 size = TextLength(state->buffer.text[r]);
            f32 textOffsetX = 0.0f;
            f32 scaleFactor = fontSize / fontBaseSize;

            for (i32 c = 0; c < size; c++) {
                i32 codepointByteCount = 0;
                i32 codepoint = GetCodepointNext(&state->buffer.text[r][c], &codepointByteCount);
                i32 index = GetGlyphIndex(state->font.font, codepoint);

                Vector2 pos = { position.x + textOffsetX, position.y + textOffsetY * r };

                textOffsetX += ((f32)state->font.font.glyphs[index].advanceX * scaleFactor + fontSpacing);

                i32 cursorPositionR = state->buffer.cursorPosition.x;
                i32 cursorPositionC = state->buffer.cursorPosition.y;
                if (state->buffer.cursorPosition.x == r && state->buffer.cursorPosition.y == c) {
                    Rectangle rect = {
                        .x = state->buffer.cursorPosition.x,
                        .y = state->buffer.cursorPosition.y,
                        .width = textOffsetX,
                        .height = fontSize
                    };
                    DrawRectangleRec(rect, WHITE);

                    DrawTextCodepoint(state->font.font, codepoint, pos, fontSize, BLACK);
                } else {
                    DrawTextCodepoint(state->font.font, codepoint, pos, fontSize, WHITE);
                }
            }
        }
    }
}
