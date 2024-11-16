#include <raylib.h>
#include <stdio.h>

#include "arena.h"
#include "draw.h"
#include "logic.h"

// TODO: make this usable on web

i32 main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "si");
    SetExitKey(0);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    SetWindowMinSize(400, 400);
    // RLAPI void SetWindowMaxSize(int width, int height);               // Set window maximum
    // dimensions (for FLAG_WINDOW_RESIZABLE) RLAPI void SetWindowSize(int width, int height); //
    // Set window dimensions

    // use this to set callback
    // void* windowhandle = GetWindowHandle();

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
