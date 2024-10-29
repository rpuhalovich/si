#ifndef LOGIC_H
#define LOGIC_H

#include "state.h"

trl_State* init();

void run(trl_State* state);

void freeState(trl_State* state);

#endif // LOGIC_H
