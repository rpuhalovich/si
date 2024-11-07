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

    Arena* arena = initArena(MEGABYTES(128));
    AppState* state = initState(arena);

    while (!WindowShouldClose()) {
        BeginDrawing();
        run(arena, state);
        draw(state);
        EndDrawing();
    }

    freeState(state);
    freeArena(arena);

    CloseWindow();
    return 0;
}
