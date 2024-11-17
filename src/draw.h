#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "appmath.h"
#include "state.h"

void drawDebugRec(Rectangle r);

void drawDebugPoint(Vector2 p);

void drawThing(const Thing* t);

void draw(AppState* state);

#endif // DRAW_H
