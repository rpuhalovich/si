#ifndef THING_H
#define THING_H

#include <raylib.h>

#include "types.h"

typedef struct {
    Rectangle bounds;
    f32 padding;
    f32 margin;
} Box;

typedef struct {
    Line* contents;
    Box box;
} Thing;

#endif // THING_H
