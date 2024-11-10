#include "draw.h"

void drawLine(Line* l, AppFont* font, Color color, Vector2 pos)
{
    drawString(l->characters, l->length, font, color, pos);
}

void drawStringbg(char* str, i32 strLen, AppFont* font, Color color, Color bg, Vector2 pos)
{
    Rectangle r = {.x = pos.x, .y = pos.y, .width = strLen * font->charWidth, .height = font->charHeight};
    DrawRectangleRec(r, bg);
    drawString(str, strLen, font, color, pos);
}

void drawString(char* str, i32 strLen, AppFont* font, Color color, Vector2 pos)
{
    Vector2 curPos = pos;
    for (i32 i = 0; i < strLen; i++) {
        i32 codepointByteCount = 0;
        char character = str[i];
        i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
        DrawTextCodepoint(font->font, codepoint, curPos, font->size, color);
        curPos.x += font->charWidth;
    }
}

void drawBuffer(Rectangle bounds, Buffer* b, AppFont* font, Color textColor, Color cursorColor)
{
    if (b->isActive) {
        Rectangle rec = {
            .x = (b->cursorPosition.x - b->scrollOffset.x) * font->charWidth + bounds.x,
            .y = (b->cursorPosition.y - b->scrollOffset.y) * font->charHeight + bounds.y,
            .width = font->charWidth,
            .height = font->charHeight};
        DrawRectangleRec(rec, cursorColor);
    }

    for (i32 r = b->scrollOffset.y; r < b->length && r < b->numCellRows + b->scrollOffset.y; r++) {
        for (i32 c = b->scrollOffset.x; c < b->lines[r]->length && c < b->numCellCols + b->scrollOffset.x; c++) {
            Vector2 curPos = {(c - b->scrollOffset.x) * font->charWidth + bounds.x, (r - b->scrollOffset.y) * font->charHeight + bounds.y};

            i32 codepointByteCount = 0;
            char character = b->lines[r]->characters[c];
            i32 codepoint = GetCodepointNext(&character, &codepointByteCount);

            DrawTextCodepoint(font->font, codepoint, curPos, font->size, textColor);
        }
    }

    for (i32 r = b->length - (i32)b->scrollOffset.y; r < b->numCellRows; r++) {
        Vector2 curPos = {.x = bounds.x, .y = r * font->charHeight};

        i32 codepointByteCount = 0;
        char character = '~';
        i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
        DrawTextCodepoint(font->font, codepoint, curPos, font->size, textColor);
    }
}

void draw(AppState* state)
{
    ClearBackground(state->color.background);

    // editor view
    {
        // DrawRectangleLinesEx(RectangleWiden(state->editor.currentBuffer.buffer->bounds, 8.f), 2.0f,
        // state->color.border);

        // editor
        Rectangle editorBounds =
            (Rectangle){state->editor.bounds.x, state->editor.bounds.y, state->editor.bounds.width, state->editor.bounds.height - state->font->charHeight};
        drawBuffer(editorBounds, state->editor.currentBuffer.buffer, state->font, state->color.foreground, state->color.cursor);

        // status line
        {
            Rectangle statusLineBounds =
                (Rectangle){state->editor.bounds.x, GetScreenHeight() - state->font->charHeight, state->editor.bounds.width, state->font->charHeight};
            DrawRectangleRec(statusLineBounds, state->color.statusLineBackGround);

            f32 curx = state->editor.bounds.x;
            f32 cury = editorBounds.height + statusLineBounds.height;
            if (state->currentMode == EDIT) {
                Line* fileName = state->editor.currentBuffer.fileName;
                Buffer* currentBuffer = state->editor.currentBuffer.buffer;

                drawLine(fileName, state->font, state->color.statusLineForeGround, (Vector2){curx, cury});
                curx += (fileName->length + 1) * state->font->charWidth;

                char str[128];
                snprintf(str, sizeof(str), "%dL %dC", (i32)currentBuffer->cursorPosition.y + 1, (i32)currentBuffer->cursorPosition.x + 1);
                drawString(str, strlen(str), state->font, state->color.statusLineForeGround, (Vector2){curx, cury});
                curx += (1 + strlen(str)) * state->font->charWidth;

                if (currentBuffer->isDirty && !currentBuffer->isScratch) {
                    f32 dirtyIndicatorOffsetY = state->editor.statusLine.bounds.y + state->font->charHeight / 2;
                    DrawCircleV((Vector2){curx, dirtyIndicatorOffsetY}, 2.f, state->color.statusLineForeGround);
                }
            }

            if (state->currentMode == OPEN_FILE) {
                char* str = "file: ";
                drawString(str, strlen(str), state->font, state->color.statusLineForeGround, (Vector2){state->editor.bounds.x, cury});

                Rectangle fileDialogBounds = (Rectangle){
                    .x = state->editor.bounds.x + strlen(str) * state->font->charWidth,
                    .y = cury,
                    .width = state->editor.bounds.width,
                    .height = state->font->charHeight};
                drawBuffer(
                    fileDialogBounds, state->editor.statusLine.statusLineInput, state->font, state->color.statusLineForeGround, state->color.statusLineCursor);
            }
        }

#ifdef DEBUG
        // debug view
        if (state->debugView.isDebugViewEnabled) {
            Vector2 start = {state->debugView.bounds.width, 0};
            Vector2 end = {state->debugView.bounds.width, state->debugView.bounds.height};
            DrawLineEx(start, end, 2.f, state->color.foreground);

            char str[128];
            Vector2 pos = {0};

            snprintf(str, sizeof(str), "FPS: %d", GetFPS());
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, pos);
            pos.y += state->font->charHeight;

            snprintf(str, sizeof(str), "FRAME TIME: %fms", GetFrameTime() * 1000);
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, pos);
            pos.y += state->font->charHeight;

            snprintf(str, sizeof(str), "ARENA CAPACITY: %f bytes", state->debugView.capacity);
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, pos);
            pos.y += state->font->charHeight;

            snprintf(str, sizeof(str), "ARENA CAPACITY PERCENT USED: %f%%", state->debugView.usedCapacity);
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, pos);
        }
#endif
    }
}
