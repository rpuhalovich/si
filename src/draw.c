#include <stdio.h>
#include "raylib.h"
#include "raygui.h"

#include "draw.h"
#include "state.h"

static int textLineSpacing = 2;

typedef struct {
    int lines;
    char** text;
} Text;

void drawText(Font font, char** text, Vector2 position, float fontSize, float spacing, Color tint);

void draw(State* state)
{
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    char** text;
    text = malloc(sizeof(char*) * 3);
    text[0] = "blahblahblah";
    text[1] = "foofoofoooooooooo";
    text[2] = "testing";

    drawText(state->font, text, (Vector2) { 0, 0 }, state->font.baseSize / 2, 1.0f, WHITE);
}

void drawText(Font font, char** text, Vector2 position, float fontSize, float spacing, Color tint)
{
    for (int i = 0; i < 3; i++) {
        float textOffsetY = fontSize + textLineSpacing;

        Vector2 pos = {
            0,
            (fontSize + textLineSpacing) * i
        };

        if (font.texture.id == 0)
            font = GetFontDefault();

        int size = TextLength(text[i]);

        float textOffsetX = 0.0f;

        float scaleFactor = fontSize/font.baseSize;

        for (int j = 0; j < size; j++) {
            int codepointByteCount = 0;
            int codepoint = GetCodepointNext(&text[i][j], &codepointByteCount);
            int index = GetGlyphIndex(font, codepoint);

            Vector2 pos = { position.x + textOffsetX, position.y + textOffsetY * i };
            DrawTextCodepoint(font, codepoint, pos, fontSize, tint);

            textOffsetX += ((float)font.glyphs[index].advanceX*scaleFactor + spacing);
        }
    }
}
