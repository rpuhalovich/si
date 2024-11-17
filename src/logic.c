#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "arena.h"
#include "box.h"
#include "colorscheme.h"
#include "file.h"
#include "logic.h"
#include "state.h"

AppState* initState(Arena* arena)
{
    AppState* state = allocate(arena, sizeof(AppState));

    // color
    {
        state->color = GetTheme(COLORSCHEME_DARK_GRUVBOX);
    }

    // TODO: https://rodneylab.com/raylib-sdf-fonts/
    // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
    // TODO: use this font for menus https://fonts.google.com/specimen/Inter
    // FIXME: raylibs font rendering is slow and shit
    // font
    {
        f32 fontResolutionScale = 4.0f;

        state->font = allocate(arena, sizeof(AppFont));
        state->font->font =
            LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 20 * fontResolutionScale, 0, 250);
        state->font->size = state->font->font.baseSize / fontResolutionScale;
        state->font->spacing = 1.0f;
        state->font->textLineSpacing = 1;

        Vector2 dpi = GetWindowScaleDPI();
        Vector2 monospaceCharDimensions =
            MeasureTextEx(state->font->font, "x", state->font->size, dpi.x);
        state->font->charWidth = monospaceCharDimensions.x;
        state->font->charHeight = monospaceCharDimensions.y;
    }

    // thing
    {
        Rectangle newBounds =
            (Rectangle){.x = 0, .y = 0, .width = 256, .height = GetScreenHeight()};
        state->thing = (Thing){
            .box = {.bounds = newBounds, .padding = 0.f, .margin = 0.f},
            .contents = newLine(arena)};

        char* str = "hellofowiejfoiewjfoiwejfowie";
        insertString(arena, state->thing.contents, str, strlen(str), 0);
    }

    // requests
    {
        state->requestlist.requests = allocate(arena, sizeof(Request));
        state->requestlist.length = 1;
        state->requestlist.capacity = 1;
        // state->requestlist.requests[0];
    }

    return state;
}

void run(Arena* arena, AppState* state)
{
    int x = 0;

    state->isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    state->mouseDownLocation = GetMousePosition();

    // thing
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            dragBoxPressed(&state->thing.box, state->mouseDownLocation);

        dragBox(&state->thing.box, state->mouseDownLocation);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            dragBoxReleased(&state->thing.box, state->mouseDownLocation);
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font->font);
}
