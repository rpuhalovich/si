#include <stdio.h>
#include "raylib.h"
#include "raygui.h"

#include "draw.h"
#include "state.h"

void draw(State* state) {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (GuiButton((Rectangle) { 24, 24, 120, 30 }, "#191#Show Message")) {
        state->showMessageBox = true;
    }

    if (state->showMessageBox) {
        char message[32];
        snprintf(message, sizeof(message), "count: %d", state->count);
        int result = GuiMessageBox(
            (Rectangle){ 85, 70, 250, 100 },
            "#191#Message Box",
            message,
            "Nice;Cool");

        if (result >= 0)
            state->showMessageBox = false;
    }

    int score = 10;
    DrawText(TextFormat("Score: %08i", score), 200, 80, 20, WHITE);
}
