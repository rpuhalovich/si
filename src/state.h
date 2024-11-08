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
    f32 charWidth;
    f32 charHeight;
} AppFont;

typedef struct {
    struct {
        i32 numCellCols;
        i32 numCellRows;
        f32 cellWidth;
        f32 cellHeight;
        i32 gridXOffset;
    } grid;

    struct {
        Color background;
        Color foreground;
        Color foregroundHighlight;
    } color;

    struct {
        Buffer* tempFileName;
    } commandLine;

    struct {
        bool isDirty;
        Buffer* fileName;
    } statusLine;

    Mode currentMode;

    AppFont* font;
    Buffer* buffer;
} AppState;

#endif // STATE_H
