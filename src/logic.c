#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "arena.h"
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
        state->thing = (Thing) {
            .box = {
                .bounds = (Rectangle) {.x = 100, .y = 100, .width = 100, .height = 100},
                .padding = 0.f,
                .margin = 0.f
            },
            .contents = newLine(arena)
        };
    }

    return state;
}

void run(Arena* arena, AppState* state)
{
    state->isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    state->mouseDownLocation = GetMousePosition();

    if (state->isMouseDown) {
        Rectangle tb = state->thing.box.bounds;

        Rectangle boundary = (Rectangle) {
                .x = state->mouseDownLocation.x + tb.x + tb.width - 5,
                .y = state->mouseDownLocation.y + tb.y + tb.height - 5,
                .width = 10,
                .height = 10};

        int hoverover = CheckCollisionPointRec(state->mouseDownLocation, boundary);
        if (hoverover)
            state->thing.box.bounds.width = state->mouseDownLocation.x - (tb.width + tb.x);
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font->font);
}
