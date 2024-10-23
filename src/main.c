#include <raylib.h>
#include <stdio.h>

#include "draw.h"
#include "logic.h"

i32 main()
{
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "test-raylib");
    SetTargetFPS(60);

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
