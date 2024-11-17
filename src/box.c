#include "box.h"

void dragBoxPressed(Box* b, Vector2 mouseLocation)
{
    f32 boxsize = 20.f;

    // isDraggingRight
    {
        Rectangle boundary = (Rectangle){
            .x = b->bounds.x + b->bounds.width - (boxsize / 2),
            .y = b->bounds.y,
            .width = boxsize,
            .height = b->bounds.height};

        int hoverover = CheckCollisionPointRec(mouseLocation, boundary);
        if (hoverover)
            b->isDraggingRight = true;
    }

    // isDragging
    {
        Rectangle boundary = (Rectangle){
            .x = b->bounds.x + b->bounds.width - (boxsize / 2),
            .y = b->bounds.y + b->bounds.height - (boxsize / 2),
            .width = boxsize,
            .height = boxsize};

        int hoverover = CheckCollisionPointRec(mouseLocation, boundary);
        if (hoverover)
            b->isDragging = true;
    }
}

void dragBox(Box* b, Vector2 mouseLocation)
{
    if (b->isDragging) {
        b->bounds.width = fmax(mouseLocation.x - b->bounds.x, 50);
        b->bounds.height = fmax(mouseLocation.y - b->bounds.y, 50);
    }

    if (b->isDraggingRight) {
        b->bounds.width = fmax(mouseLocation.x - b->bounds.x, 50);
    }
}

void dragBoxReleased(Box* b, Vector2 mouseLocation)
{
    b->isDragging = false;
    b->isDraggingRight = false;
}
