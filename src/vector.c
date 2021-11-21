#include "vector.h"
#include <stdlib.h>

// constructor for Pair
vector_t *create_vector(float x_, float y_) {
    vector_t *vector = (vector_t *) malloc(sizeof(vector_t));
    vector->x = x_;
    vector->y = x_;

    return vector;
}
