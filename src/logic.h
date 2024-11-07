#ifndef LOGIC_H
#define LOGIC_H

#include "arena.h"
#include "state.h"

AppState* initState(Arena* arena);

void run(Arena* arena, AppState* state);

void freeState(AppState* state);

#endif // LOGIC_H
