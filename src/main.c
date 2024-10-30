#include <raylib.h>
#include <stdio.h>

#include "draw.h"
#include "logic.h"

i32 main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "");
    SetTargetFPS(60);

    AppState* state = init();
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
