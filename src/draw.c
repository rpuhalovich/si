#include "draw.h"

#include "thing.h"

#ifdef DEBUG
#define DRAW_DEBUG_REC(r) drawDebugRec(r)
#define DRAW_DEBUG_POINT(p) drawDebugPoint(p)
#else
#define DRAW_DEBUG_REC(r)
#define DRAW_DEBUG_POINT(p, c)
#endif

void drawDebugRec(Rectangle r)
{
    char coordstr[64];

    snprintf(coordstr, sizeof(coordstr), "(x: %.2f, y: %.2f)", r.x, r.y);
    DrawText(coordstr, r.x, r.y - 24, 8.f, PINK);

    snprintf(coordstr, sizeof(coordstr), "(w: %.2f, h: %.2f)", r.width, r.height);
    DrawText(coordstr, r.x, r.y - 12, 8.f, PINK);

    DrawRectangleLinesEx(r, 2.0f, PINK);
}

void drawDebugPoint(Vector2 p)
{
    DrawRectangleRec((Rectangle){.x = p.x - 5, .y = p.y - 5, .width = 10, .height = 10}, RED);
}

void drawThing(const Thing* t)
{
    Rectangle bounds = t->box.bounds;

    DrawRectangleRec(bounds, WHITE);

    f32 xpos = bounds.x + (bounds.width / 2);
    f32 ypos = bounds.y + (bounds.height / 2);
    DrawText(t->contents->characters, xpos, ypos, 8.f, BLUE);

    DRAW_DEBUG_REC(t->box.bounds);
}

void draw(AppState* state)
{
    ClearBackground(BLACK);
    Vector2 scale = GetWindowScaleDPI();

    drawThing(&state->thing);

#ifdef DEBUG
    Rectangle tb = state->thing.box.bounds;

    Vector2 point = (Vector2){.x = tb.x + tb.width, .y = tb.y + tb.height};
    DRAW_DEBUG_POINT(point);

    if (state->isMouseDown) {
        DrawRectangleRec(
            (Rectangle){
                .x = state->mouseDownLocation.x - 5,
                .y = state->mouseDownLocation.y - 5,
                .width = 10,
                .height = 10},
            BLUE);
    }
#endif
}
