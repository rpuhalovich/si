#ifndef LOGIC_H
#define LOGIC_H

#include "state.h"

AppState* init();

void run(AppState* state);

void freeState(AppState* state);

#endif // LOGIC_H
