#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "buffer.h"
#include "colorscheme.h"
#include "thing.h"
#include "types.h"

typedef struct {
    Font font;
    f32 size;
    f32 spacing;
    i32 textLineSpacing;
    f32 charWidth;
    f32 charHeight;
} AppFont;

typedef struct {
    ColorScheme color;
    AppFont* font;
    i32 currentTargetFps;

    bool isMouseDown;
    Vector2 mouseDownLocation;

    Thing thing;
} AppState;

#endif // STATE_H
