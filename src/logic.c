#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appmath.h"
#include "arena.h"
#include "colorscheme.h"
#include "file.h"
#include "logic.h"
#include "state.h"

AppState* initState(Arena* arena)
{
    AppState* state = allocate(arena, sizeof(AppState));

    // color
    {
        state->color = GetTheme(COLORSCHEME_DARK_GRUVBOX);
    }

    // TODO: https://rodneylab.com/raylib-sdf-fonts/
    // TODO: https://devcodef1.com/news/1401333/raylib-freetype-font-rendering
    // TODO: use this font for menus https://fonts.google.com/specimen/Inter
    // FIXME: raylibs font rendering is slow and shit
    // font
    {
        f32 fontResolutionScale = 4.0f;

        state->font = allocate(arena, sizeof(AppFont));
        state->font->font =
            LoadFontEx("res/JetBrainsMonoNL-Regular.ttf", 20 * fontResolutionScale, 0, 250);
        state->font->size = state->font->font.baseSize / fontResolutionScale;
        state->font->spacing = 1.0f;
        state->font->textLineSpacing = 1;

        Vector2 dpi = GetWindowScaleDPI();
        Vector2 monospaceCharDimensions =
            MeasureTextEx(state->font->font, "x", state->font->size, dpi.x);
        state->font->charWidth = monospaceCharDimensions.x;
        state->font->charHeight = monospaceCharDimensions.y;
    }

    // editor
    {
        Buffer* b = newBuffer(arena);
        b->isScratch = true;
        state->editorView.currentBuffer.buffer = b;
        state->editorView.currentBuffer.buffer->isActive = true;
        state->editorView.currentBuffer.fileName = newLine(arena);
        char* scratchName = "[SCRATCH]";
        insertString(
            arena, state->editorView.currentBuffer.fileName, scratchName, strlen(scratchName), 0);

        state->editorView.statusLine.statusLineInput = newBuffer(arena);

        state->editorView.bounds =
            (Rectangle){.x = 0, .y = 0, .width = GetScreenWidth(), .height = GetScreenHeight()};
    }

    return state;
}

void run(Arena* arena, AppState* state)
{
    // window resize
    {
        state->editorView.bounds = (Rectangle){
            .x = 0,
            .y = 0,
            .width = GetScreenWidth(),
            .height = GetScreenHeight() - state->font->charHeight};

#ifdef DEBUG
        if (state->debugView.isDebugViewEnabled) {
            f32 offset = 500.f;

            state->editorView.bounds.x = offset;
            state->editorView.bounds.width = GetScreenWidth() - offset;
            state->debugView.bounds.width = offset;
            state->debugView.bounds.height = GetScreenHeight();
        } else {
            state->editorView.bounds.x = 0.f;
            state->editorView.bounds.width = GetScreenWidth();
        }
#endif

        state->editorView.currentBuffer.buffer->numCellCols =
            state->editorView.bounds.width / state->font->charWidth - 1;
        state->editorView.currentBuffer.buffer->numCellRows =
            state->editorView.bounds.height / state->font->charHeight;

        state->editorView.statusLine.statusLineInput->numCellRows = 1;
        state->editorView.statusLine.statusLineInput->numCellCols =
            state->editorView.currentBuffer.buffer->numCellCols;

        state->editorView.currentBuffer.buffer->numCellCols =
            state->editorView.bounds.width / state->font->charWidth - 1;
        state->editorView.currentBuffer.buffer->numCellRows =
            state->editorView.bounds.height / state->font->charHeight;

#ifdef RELEASE
        i32 monitorRefreshRate = GetMonitorRefreshRate(GetCurrentMonitor());
        if (state->currentTargetFps != monitorRefreshRate) {
            SetTargetFPS(monitorRefreshRate);
            state->currentTargetFps = monitorRefreshRate;
        }
#endif
    }

#ifdef DEBUG
    // debug properties
    {
        state->debugView.usedCapacity = ((f32)arena->usedCapacity / arena->capacity) * 100;
        state->debugView.capacity = arena->capacity;
    }
#endif

    // input
    {
        Buffer* b = NULL;
        if (state->editorView.currentEditMode == EDITOR_MODE_EDIT) {
            b = state->editorView.currentBuffer.buffer;
        }
        if (state->editorView.currentEditMode == EDITOR_MODE_OPEN_FILE) {
            b = state->editorView.statusLine.statusLineInput;
        }

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
            moveCursorRight(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_F) || IsKeyPressedRepeat(KEY_F))) {
            moveCursorRight(b);
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
            moveCursorLeft(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_B) || IsKeyPressedRepeat(KEY_B))) {
            moveCursorLeft(b);
        }

        if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
            moveCursorUp(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_P) || IsKeyPressedRepeat(KEY_P))) {
            moveCursorUp(b);
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
            moveCursorDown(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N))) {
            moveCursorDown(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D))) {
            deletec(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E)) {
            moveCursorEndOfLine(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A)) {
            moveCursorBeginningOfLine(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S) &&
            state->editorView.currentEditMode == EDITOR_MODE_EDIT) {
            zeroUnusedCapacity(b);
            write(b, state->editorView.currentBuffer.fileName);
            b->isDirty = false;
        }

        if (IsKeyPressed(KEY_TAB) || IsKeyPressedRepeat(KEY_TAB)) {
            insertTab(arena, b);
        }

        if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_K)) || IsKeyPressedRepeat(KEY_K)) {
            killl(b);
        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
            if (b) {
                b->isActive = false;
            }

            clearLine(state->editorView.statusLine.statusLineInput->lines[0]);
            state->editorView.statusLine.statusLineInput->cursorPosition.x = 0;
            state->editorView.statusLine.statusLineInput->isActive = true;
            state->editorView.currentEditMode = EDITOR_MODE_OPEN_FILE;
        }

        if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
            backspace(arena, b);
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER)) {
            if (state->editorView.currentEditMode == EDITOR_MODE_EDIT) {
                enter(arena, b);
            }

            if (state->editorView.currentEditMode == EDITOR_MODE_OPEN_FILE) {
                state->editorView.currentEditMode = EDITOR_MODE_EDIT;
                if (b) {
                    b->isActive = false;
                }

                Line* fileName = state->editorView.statusLine.statusLineInput->lines[0];
                Buffer* newBuffer = load(arena, fileName);
                if (newBuffer != NULL) {
                    state->editorView.currentBuffer.buffer = newBuffer;
                    state->editorView.currentBuffer.fileName = fileName;
                }

                state->editorView.currentBuffer.buffer->isActive = true;
            }
        }

        char c;
        while ((c = GetCharPressed())) {
            typeCharb(arena, b, c);
        }

#ifdef DEBUG
        if (IsKeyPressed(KEY_F9)) {
            state->debugView.isDebugViewEnabled = !state->debugView.isDebugViewEnabled;
        }

        if (IsKeyPressed(KEY_F6)) {
            state->canvasView.isCanvasViewEnabled = !state->canvasView.isCanvasViewEnabled;
        }

        if (IsKeyPressed(KEY_F5)) {
            char str[128];
            snprintf(str, sizeof(str), "%s/tmp", getenv("HOME"));
            Line* fileName = newLines(arena, str);
            state->editorView.currentBuffer.buffer = load(arena, fileName);
            state->editorView.currentBuffer.fileName = fileName;
            state->editorView.currentBuffer.buffer->isActive = true;
        }
#endif
    }
}

void freeState(AppState* state)
{
    UnloadFont(state->font->font);
}
