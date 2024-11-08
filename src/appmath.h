#ifndef APPMATH_H
#define APPMATH_H

#include <raylib.h>

#include "types.h"

i32 iclamp(i32 val, i32 min, i32 max);
i32 imin(i32 val, i32 min);
i32 imax(i32 val, i32 max);

Rectangle RectangleWiden(Rectangle r, f32 amt);

#endif // APPMATH_H
