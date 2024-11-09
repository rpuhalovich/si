#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "buffer.h"
#include "colorscheme.h"
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
    /*
    struct {
        // TODO: implement
    } menuBar;
    */

    struct {
        struct {
            Buffer* statusLineInput;
            Rectangle bounds;
        } statusLine;

        struct {
            Line* fileName;
            Buffer* buffer;
        } currentBuffer;

        Rectangle bounds;
    } editor;

    ColorScheme color;

    Mode currentMode;

    AppFont* font;

    i32 currentTargetFps;

#ifdef DEBUG
    struct {
        bool isDebugViewEnabled;
        float usedCapacity;
        float capacity;

        Rectangle bounds;
    } debugView;
#endif
} AppState;

#endif // STATE_H
