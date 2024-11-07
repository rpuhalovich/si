#include <raylib.h>
#include <stdio.h>

#include "arena.h"
#include "draw.h"
#include "logic.h"

i32 main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "");
    SetTargetFPS(60);
    SetExitKey(0);

    Arena* stateArena = initArena(MEGABYTES(128));
    AppState* state = initState(stateArena);

    while (!WindowShouldClose()) {
        BeginDrawing();
        run(stateArena, state);
        draw(state);
        EndDrawing();
    }

    freeState(state);
    freeArena(stateArena);

    CloseWindow();
    return 0;
}
