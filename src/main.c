#include <stdio.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "dark/style_dark.h"

#include "logic.h"
#include "draw.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "test-raylib");
    SetTargetFPS(60);
    GuiLoadStyleDark();

    State* state = init();
    while (!WindowShouldClose()) {
        BeginDrawing();
        run(state);
        draw(state);
        EndDrawing();
    }
    freeState(state);

    CloseWindow();
    return 0;
}
