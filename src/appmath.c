#include "appmath.h"

i32 iclamp(i32 val, i32 min, i32 max)
{
    if (val > max)
        return max;
    if (val < min)
        return min;
    return val;
}

i32 imin(i32 val, i32 min)
{
    return val < min ? min : val;
}

i32 imax(i32 val, i32 max)
{
    return val > max ? max : val;
}

Rectangle RectangleWiden(Rectangle r, f32 amt)
{
    return (Rectangle){
        .x = r.x - amt, .y = r.y - amt, .width = r.width + amt * 2, .height = r.height + amt * 2};
}
