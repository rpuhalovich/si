#include "appmath.h"

i32 iclamp(i32 val, i32 min, i32 max)
{
    if (val > max)
        return max;
    if (val < min)
        return min;
    return val;
}
