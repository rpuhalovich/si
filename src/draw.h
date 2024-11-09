#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "appmath.h"
#include "state.h"

void drawStringbg(char* str, i32 strLen, AppFont* font, Color color, Color bg, Vector2 pos);

void drawLine(Line* l, AppFont* font, Color color, Vector2 pos);

void drawString(char* str, i32 strLen, AppFont* font, Color color, Vector2 pos);

void drawBuffer(Buffer* b, AppFont* font, Color textColor, Color cursorColor);

void draw(AppState* state);

#endif // DRAW_H
