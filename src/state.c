#include <stdlib.h>

#include "state.h"

void freeState(State* state) {
    free(state);
}
