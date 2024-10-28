#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "logic.h"
#include "raylib.h"
#include "state.h"

State* init()
{
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    State* state = malloc(sizeof(State));
    memset(state, 0, sizeof(State));

    // font
    {
        // TODO: https://rodneylab.com/raylib-sdf-fonts/
        // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
        state->font.font = LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 32, 0, 250);
        state->font.size = state->font.font.baseSize / 2;
        state->font.spacing = 1.0f;
        state->font.textLineSpacing = 2;
    }

    // buffer
    {
        state->buffer.lines = 2;
        state->buffer.text = malloc(sizeof(char*) * state->buffer.lines);
        state->buffer.text[0] = "blahblahblah";
        state->buffer.text[1] = "foofoofoooooooooo";
        // state->buffer.text[2] = "testing";

        state->buffer.cursorPosition = (Vector2) { 0, 0 };
    }

    return state;
}

void run(State* state)
{
    if (IsKeyPressed(KEY_RIGHT))
        state->buffer.cursorPosition.x++;

    if (IsKeyPressed(KEY_LEFT))
        state->buffer.cursorPosition.x--;

    if (IsKeyPressed(KEY_UP))
        state->buffer.cursorPosition.y--;

    if (IsKeyPressed(KEY_DOWN))
        state->buffer.cursorPosition.y++;
}

void freeState(State* state)
{
    UnloadFont(state->font.font);
    free(state->buffer.text);
    free(state);
}
