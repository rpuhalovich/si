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
        drawBuffer(state->buffer, state->font, BLACK);
    }

    // status line
    {
        DrawRectangleRec(state->statusLine.fileName->bounds, BLACK);
        drawBuffer(state->statusLine.fileName, state->font, BEIGE);

        // drawBuffer(state->commandLine.tempFileName, state->font, BLACK);

        // Vector2 pos = {0, GetScreenHeight() - state->grid.cellHeight};
        // Rectangle rect = {
        //     .x = pos.x, .y = pos.y, .width = GetScreenWidth(), .height = state->grid.cellHeight};
        // DrawRectangleRec(rect, state->color.foreground);

        // Line* l;
        // if (state->currentMode == EDIT)
        //     l = state->file.fileName;
        // if (state->currentMode == OPEN_FILE) {
        //     l = state->commandLine.tempFileName->lines[0];
        // }

        // drawLine(l, state->font, WHITE, pos);

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
