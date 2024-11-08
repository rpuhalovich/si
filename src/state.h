#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "buffer.h"
#include "types.h"

typedef enum {
    EDIT,
    OPEN_FILE
} Mode;

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
        i32 gridXOffset;

        Rectangle editorBounds;
    } grid;

    struct {
        Color background;
        Color foreground;
        Color foregroundHighlight;
    } color;

    struct {
        Line* tempFileName;
        i32 column;
    } commandLine;

    Mode currentMode;

    AppFont font;
    Buffer buffer;
} AppState;

#endif // STATE_H
