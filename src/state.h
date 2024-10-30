#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "buffer.h"
#include "types.h"

// used for drawing
typedef struct {
    Font font;
    f32 size;
    f32 spacing;
    i32 textLineSpacing;
} AppFont;

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

    AppFont font;
    Buffer buffer;
} AppState;

#endif // STATE_H
