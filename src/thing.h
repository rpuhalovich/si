#ifndef THING_H
#define THING_H

#include <raylib.h>

#include "box.h"
#include "line.h"
#include "types.h"

typedef struct {
    Line* contents;
    Box box;
} Thing;

#endif // THING_H
