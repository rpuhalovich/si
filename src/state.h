#ifndef STATE_H
#define STATE_H

#include "raylib.h"
#include "types.h"

typedef struct {
    i32 count;
    bool showMessageBox;

    // used for drawing
    struct {
        Font font;
        f32 size;
        f32 spacing;
        i32 textLineSpacing;
    } font;

    // used for logic
    struct {
        i32 lines;
        char** text;
        Vector2 cursorPosition;
    } buffer;
} State;

#endif // STATE_H
