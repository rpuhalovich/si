#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "appmath.h"
#include "state.h"

void drawLine(Line* l, AppFont* font, Color color, Vector2 pos);

// considers cursor position
void drawBuffer(Buffer* b, AppFont* font, Color color);

void draw(AppState* state);

#endif // DRAW_H
