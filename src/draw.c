#include "draw.h"

void drawLine(Line* l, AppFont* font, Color color, Vector2 pos)
{
    Vector2 curPos = pos;
    for (i32 i = 0; i < l->length; i++) {
        i32 codepointByteCount = 0;
        char character = l->characters[i];
        i32 codepoint = GetCodepointNext(&character, &codepointByteCount);
        DrawTextCodepoint(font->font, codepoint, curPos, font->size, color);
        curPos.x += font->charWidth;
    }
}

void drawBuffer(Buffer* b, AppFont* font, Color textColor, Color cursorColor)
{
    // DrawRectangleRec(b->bounds, DARKBLUE);

    i32 numCellCols = b->bounds.width / font->charWidth;
    i32 numCellRows = b->bounds.height / font->charHeight;

    if (b->isActive) {
        Rectangle rec = {
            .x = (b->cursorPosition.x - b->scrollOffset.x) * font->charWidth + b->bounds.x,
            .y = (b->cursorPosition.y - b->scrollOffset.y) * font->charHeight + b->bounds.y,
            .width = font->charWidth,
            .height = font->charHeight};
        DrawRectangleRec(rec, cursorColor);
    }

    for (i32 r = b->scrollOffset.y; r < b->length && r < numCellRows + b->scrollOffset.y; r++) {
        for (i32 c = b->scrollOffset.x; c < b->lines[r]->length && c < numCellCols + b->scrollOffset.x; c++) {
            Vector2 curPos = {
                (c - b->scrollOffset.x) * font->charWidth + b->bounds.x,
                (r - b->scrollOffset.y) * font->charHeight + b->bounds.y};

            i32 codepointByteCount = 0;
            char character = b->lines[r]->characters[c];
            i32 codepoint = GetCodepointNext(&character, &codepointByteCount);

            DrawTextCodepoint(font->font, codepoint, curPos, font->size, textColor);
        }
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
        DrawRectangleRec(state->statusLine.bounds, state->color.statusLineBackground);
        drawLine(
            state->currentBuffer.fileName,
            state->font,
            state->color.statusLineForeGround,
            (Vector2){state->statusLine.bounds.x, state->statusLine.bounds.y});

        if (state->currentBuffer.buffer->isDirty) {
            f32 dirtyIndicatorOffsetX = (state->currentBuffer.fileName->length + 1) * state->font->charWidth;
            f32 dirtyIndicatorOffsetY = state->statusLine.bounds.y + state->font->charHeight / 2;
            DrawCircleV(
                (Vector2){dirtyIndicatorOffsetX, dirtyIndicatorOffsetY},
                2.f,
                state->color.statusLineForeGround);
        }
    }
}
