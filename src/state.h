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
    struct {
        i32 numCellCols;
        i32 numCellRows;
        i32 cellWidth;
        i32 cellHeight;
    } grid;

    struct {
        Color background;
        Color foreground;
        Color foregroundHighlight;
    } color;

    trl_Font font;
    Buffer buffer;
} AppState;

#endif // STATE_H
