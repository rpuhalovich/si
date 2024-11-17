#include "draw.h"

#include "thing.h"

#ifdef DEBUG
#define DRAW_DEBUG_REC(r) drawDebugRec(r)
#define DRAW_DEBUG_POINT(p) drawDebugPoint(p)
#else
#define DRAW_DEBUG_REC(r)
#define DRAW_DEBUG_POINT(p)
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

void drawDebugPoint(Vector2 pos)
{
    DrawRectangleRec((Rectangle) {.x = pos.x - 5, .y = pos.y - 5, .width = 10, .height = 10}, RED);
}

void draw(AppState* state)
{
    ClearBackground(BLACK);

    // thing
    {
        DrawRectangleRounded(state->thing.box.bounds, 0.1f, 16, WHITE);
        DRAW_DEBUG_REC(state->thing.box.bounds);
    }

#ifdef DEBUG
    Rectangle tb = state->thing.box.bounds;

    Vector2 point = (Vector2) {.x = tb.x + tb.width, .y = tb.y + tb.height};
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
