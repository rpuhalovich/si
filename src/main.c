#include <raylib.h>
#include <stdio.h>

#include "arena.h"
#include "draw.h"
#include "logic.h"

i32 main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

    InitWindow(1280, 720, "");
    SetExitKey(0);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
    SetWindowMinSize(400, 400);

    Arena* arena = initArena(MEGABYTES(16));
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
