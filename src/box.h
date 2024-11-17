#ifndef BOX_H
#define BOX_H

#include <math.h>
#include <raylib.h>

#include "types.h"

typedef struct {
    Rectangle bounds;
    f32 padding;
    f32 margin;
    bool isDragging;
    bool isDraggingRight;
} Box;

void dragBoxPressed(Box* b, Vector2 mouseLocation);

void dragBox(Box* b, Vector2 mouseLocation);

void dragBoxReleased(Box* b, Vector2 mouseLocation);

#endif // BOX_H
