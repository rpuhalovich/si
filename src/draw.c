#include "draw.h"

Rectangle RectangleWiden(Rectangle r, f32 amt)
{
    return (Rectangle){
        .x = r.x - amt, .y = r.y - amt, .width = r.width + amt * 2, .height = r.height + amt * 2};
}

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

void drawBuffer(Buffer* b, AppFont* font, Color color)
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
        DrawRectangleRec(rec, GRAY);
    }

    for (i32 r = b->scrollOffset.y; r < b->length && r < numCellRows + b->scrollOffset.y; r++) {
        for (i32 c = b->scrollOffset.x; c < b->lines[r]->length && c < numCellCols + b->scrollOffset.x; c++) {
            Vector2 curPos = {
                (c - b->scrollOffset.x) * font->charWidth + b->bounds.x,
                (r - b->scrollOffset.y) * font->charHeight + b->bounds.y};

            i32 codepointByteCount = 0;
            char character = b->lines[r]->characters[c];
            i32 codepoint = GetCodepointNext(&character, &codepointByteCount);

            DrawTextCodepoint(font->font, codepoint, curPos, font->size, color);
        }
    }
}

void draw(AppState* state)
{
    ClearBackground(state->color.background);

    // editor
    {
        DrawRectangleLinesEx(RectangleWiden(state->buffer->bounds, 8.f), 2.0f, BLACK);
        drawBuffer(state->buffer, state->font, BLACK);
    }

    // status line
    {
        DrawRectangleRec(state->statusLine.fileName->bounds, BLACK);
        drawBuffer(state->statusLine.fileName, state->font, BEIGE);
    }
}
