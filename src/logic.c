#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "raylib.h"
#include "logic.h"
#include "state.h"

State* init() {
    State* state = malloc(sizeof(State));
    memset(state, 0, sizeof(State));

    // TODO: https://rodneylab.com/raylib-sdf-fonts/
    // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
    state->font = LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 32, 0, 250);
    state->count = 10;
    state->showMessageBox = false;

    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    return state;
}

void run(State* state) {
}

void freeState(State* state) {
    UnloadFont(state->font);

    free(state);
}
