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

void drawBuffer(Buffer* b, AppFont* font, Color textColor, Color cursorColor)
{
    if (b->isActive) {
        Rectangle rec = {
            .x = (b->cursorPosition.x - b->scrollOffset.x) * font->charWidth + b->bounds.x,
            .y = (b->cursorPosition.y - b->scrollOffset.y) * font->charHeight + b->bounds.y,
            .width = font->charWidth,
            .height = font->charHeight};
        DrawRectangleRec(rec, cursorColor);
    }

    for (i32 r = b->scrollOffset.y; r < b->length && r < b->numCellRows + b->scrollOffset.y; r++) {
        for (i32 c = b->scrollOffset.x; c < b->lines[r]->length && c < b->numCellCols + b->scrollOffset.x;
             c++) {
            Vector2 curPos = {
                (c - b->scrollOffset.x) * font->charWidth + b->bounds.x,
                (r - b->scrollOffset.y) * font->charHeight + b->bounds.y};

            i32 codepointByteCount = 0;
            char character = b->lines[r]->characters[c];
            i32 codepoint = GetCodepointNext(&character, &codepointByteCount);

            DrawTextCodepoint(font->font, codepoint, curPos, font->size, textColor);
        }
    }

    for (i32 r = b->length; r < b->numCellRows; r++) {
        Vector2 curPos = {.x = b->bounds.x, .y = r * font->charHeight};

        i32 codepointByteCount = 0;
        char character = '~';
        i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
        DrawTextCodepoint(font->font, codepoint, curPos, font->size, textColor);
    }
}

void draw(AppState* state)
{
    ClearBackground(state->color.background);

    // editor
    {
        DrawRectangleLinesEx(
            RectangleWiden(state->currentBuffer.buffer->bounds, 8.f), 2.0f, state->color.border);
        drawBuffer(state->currentBuffer.buffer, state->font, state->color.foreground, state->color.cursor);
    }

    // status line
    {
        DrawRectangleRec(state->statusLine.bounds, state->color.statusLineBackGround);

        if (state->currentMode == EDIT) {
            drawLine(
                state->currentBuffer.fileName,
                state->font,
                state->color.statusLineForeGround,
                (Vector2){state->statusLine.bounds.x, state->statusLine.bounds.y});

            if (state->currentBuffer.buffer->isDirty && !state->currentBuffer.buffer->isScratch) {
                f32 dirtyIndicatorOffsetX =
                    (state->currentBuffer.fileName->length + 1) * state->font->charWidth;
                f32 dirtyIndicatorOffsetY = state->statusLine.bounds.y + state->font->charHeight / 2;
                DrawCircleV(
                    (Vector2){dirtyIndicatorOffsetX, dirtyIndicatorOffsetY},
                    2.f,
                    state->color.statusLineForeGround);
            }
        }

        if (state->currentMode == OPEN_FILE) {
            char* str = "file: ";
            drawString(
                str,
                strlen(str),
                state->font,
                state->color.statusLineForeGround,
                (Vector2){state->statusLine.bounds.x, state->statusLine.bounds.y});

            // probs shouldn't be mutating bounds like this
            state->statusLine.statusLineInput->bounds.y = state->statusLine.bounds.y;
            state->statusLine.statusLineInput->bounds.x = (strlen(str) * state->font->charWidth);
            drawBuffer(
                state->statusLine.statusLineInput,
                state->font,
                state->color.statusLineForeGround,
                state->color.statusLineCursor);
        }

#ifdef DEBUG
        // debug view
        if (state->isDebugViewEnabled) {
            char str[128];

            snprintf(str, sizeof(str), "FPS: %d", GetFPS());
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, (Vector2){16, 16});

            snprintf(str, sizeof(str), "FRAME TIME: %fms", GetFrameTime() * 1000);
            drawStringbg(str, strlen(str), state->font, WHITE, BLACK, (Vector2){16, 32});
        }
#endif
    }
}
