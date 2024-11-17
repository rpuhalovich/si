#ifndef THING_H
#define THING_H

#include <raylib.h>

#include "line.h"
#include "types.h"

typedef struct {
    Rectangle bounds;
    f32 padding;
    f32 margin;
    bool isDragging;
} Box;

typedef struct {
    Line* contents;
    Box box;
} Thing;

#endif // THING_H
