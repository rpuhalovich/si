#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "dark/style_dark.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "raygui - controls test suite");
    SetTargetFPS(60);
    MaximizeWindow();

    bool showMessageBox = false;
    GuiLoadStyleDark();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (GuiButton((Rectangle) { 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

        if (showMessageBox) {
            int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 }, "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

            if (result >= 0)
                showMessageBox = false;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
