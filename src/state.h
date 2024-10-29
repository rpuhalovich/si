#ifndef STATE_H
#define STATE_H

#include "raylib.h"
#include "types.h"

// used for logic
typedef struct {
    i32 lines;
    char** text;
    Vector2 cursorPosition;
} Buffer;

// used for drawing
typedef struct {
    Font font;
    f32 size;
    f32 spacing;
    i32 textLineSpacing;
} trl_Font;

typedef struct {
    trl_Font font;
    Buffer buffer;
} trl_State;

#endif // STATE_H
