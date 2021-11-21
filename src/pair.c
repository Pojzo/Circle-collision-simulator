#include "pair.h"
#include <stdlib.h>

// constructor for Pair
pair_t *create_pair(float x_, float y_) {
    pair_t *pair = (pair_t *) malloc(sizeof(pair_t));
    pair->x = x_;
    pair->y = x_;

    return pair;
}
