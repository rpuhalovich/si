#ifndef LOGIC_H
#define LOGIC_H

#include "state.h"

State* init();

void run(State* state);

void freeState(State* state);

#endif // LOGIC_H
