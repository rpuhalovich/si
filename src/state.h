#ifndef STATE_H
#define STATE_H

#include "types.h"

typedef struct {
    i32 count;
    bool showMessageBox;
} State;

void freeState(State* state);

#endif // STATE_H
