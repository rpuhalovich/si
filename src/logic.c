#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logic.h"

State* init() {
    State* state = malloc(sizeof(State));
    memset(state, 0, sizeof(State));

    state->count = 10;
    state->showMessageBox = false;

    return state;
}

void run(State* state) {
}
