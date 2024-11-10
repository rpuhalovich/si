#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "buffer.h"
#include "colorscheme.h"
#include "types.h"

typedef enum {
    EDITOR_MODE_EDIT,
    EDITOR_MODE_OPEN_FILE
} EditorMode;

typedef enum {
    APP_MODE_APP,
    APP_MODE_COMPONENTCANVAS
} AppView;

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

        EditorMode currentEditMode;
        Rectangle bounds;
    } editorView;

#ifdef DEBUG
    struct {
        bool isDebugViewEnabled;
        float usedCapacity;
        float capacity;

        Rectangle bounds;
    } debugView;

    struct {
        bool isCanvasViewEnabled;
    } canvasView;
#endif

    AppView currentAppView;

    ColorScheme color;

    AppFont* font;

    i32 currentTargetFps;
} AppState;

#endif // STATE_H
