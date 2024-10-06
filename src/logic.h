#ifndef LOGIC_H
#define LOGIC_H

#include "state.h"

State* init();

// NOTE: mutates state
void run(State* state);

void freeState(State* state);

#endif // LOGIC_H
