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

void drawBuffer(Buffer* b, AppFont* font, Color color)
{
    DrawRectangleRec(b->bounds, DARKBLUE);

    i32 numCellCols = b->bounds.width / font->charWidth - 1;
    i32 numCellRows = b->bounds.height / font->charHeight;

    Rectangle rec = {
        .x = (b->cursorPosition.x - b->scrollOffset.x) * font->charWidth + b->bounds.x,
        .y = b->cursorPosition.y * font->charHeight + b->bounds.y,
        .width = font->charWidth,
        .height = font->charHeight};
    DrawRectangleRec(rec, GRAY);

    for (i32 r = 0; r < b->length && r < numCellRows; r++) {
        for (i32 c = b->scrollOffset.x; c < b->lines[r]->length && c < numCellCols + b->scrollOffset.x; c++) {
            Vector2 curPos = {
                (c - b->scrollOffset.x) * font->charWidth + b->bounds.x, r * font->charHeight + b->bounds.y};

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
        drawBuffer(state->buffer, state->font, WHITE);
    }

    // status line
    {
        Vector2 pos = {0, GetScreenHeight() - state->grid.cellHeight};
        Rectangle rect = {
            .x = pos.x, .y = pos.y, .width = GetScreenWidth(), .height = state->grid.cellHeight};
        DrawRectangleRec(rect, state->color.foreground);

        Line* l;
        if (state->currentMode == EDIT)
            l = state->file.fileName;
        if (state->currentMode == OPEN_FILE) {
            l = state->commandLine.tempFileName->lines[0];
        }

        drawLine(l, state->font, WHITE, pos);

        // for (i32 i = 0; i < l->length; i++) {
        //     i32 codepoint = getCharCodePoint(l->characters[i]);

        //     Rectangle rect = {
        //         .x = state->commandLine.tempFileName->cursorPosition.x * state->grid.cellWidth,
        //         .y = pos.y,
        //         .width = state->grid.cellWidth,
        //         .height = state->grid.cellHeight};
        //     DrawRectangleRec(rect, GRAY);

        //     DrawTextCodepoint(
        //         state->font->font, codepoint, pos, state->font->size, state->color.foregroundHighlight);

        //     pos.x += state->grid.cellWidth;
        // }
    }
}
