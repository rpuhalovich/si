#include <stdio.h>
#include "raylib.h"
#include "raygui.h"

#include "draw.h"
#include "state.h"

static int textLineSpacing = 2;

void drawText(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);

void draw(State* state) {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    char* text[100];
    text[0] = "blahblahblah";
    text[1] = "foofoofoooooooooo";
    text[2] = "testing";

    for (int i = 0; i < 3; i++) {
        float fontSize = state->font.baseSize / 2;
        float textOffsetY = fontSize + textLineSpacing;

        Vector2 pos = {
            0,
            (fontSize + textLineSpacing) * i
        };

        drawText(state->font, text[i], pos, fontSize, 1.f, WHITE);
    }
}

void drawText(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint)
{
    if (font.texture.id == 0)
        font = GetFontDefault();

    int size = TextLength(text);

    float textOffsetX = 0.0f;

    float scaleFactor = fontSize/font.baseSize;

    for (int i = 0; i < size; i++) {
        int codepointByteCount = 0;
        int codepoint = GetCodepointNext(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        Vector2 pos = { position.x + textOffsetX, position.y };
        DrawTextCodepoint(font, codepoint, pos, fontSize, tint);

        textOffsetX += ((float)font.glyphs[index].advanceX*scaleFactor + spacing);
    }
}
