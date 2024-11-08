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
        Color background;
        Color foreground;
        Color foregroundHighlight;
        Color cursor;
        Color border;
        Color statusLineBackground;
        Color statusLineForeGround;
        Color statusLineCursor;
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
