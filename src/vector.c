#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// constructor for Pair
vector_t *vector_create(float x_, float y_) {
    vector_t *vector = (vector_t *) malloc(sizeof(vector_t));
    vector->x = x_;
    vector->y = y_;

    return vector;
}

// perform dot product on two vectors 
float vector_dot_product(vector_t *first, vector_t *second) {
    assert(first != NULL && second != NULL) ;
    float result = first->x * second->x + first->y * second->y;

    return result;
}

// multiply vector by scalar, return pointer to new vector
vector_t *vector_multiply(vector_t *v, float l) {
    assert(v != NULL);
    return vector_create(v->x * l, v->y * l);
}

// subtract two vectors, return pointer to new vector
vector_t *vector_subtract(vector_t *first, vector_t *second) {
    assert(first != NULL && second != NULL);
    return vector_create(first->x - second->x, first->y - second->y);
}

// return copy of vector
vector_t *vector_copy(vector_t *v) {
    assert(v != NULL);
    return vector_create(v->x, v->y);
}

// free vector from memory
void vector_free(vector_t *v) {
    free(v);
}

// print x and y coordinates of vector
void vector_print(vector_t *v) {
    printf("x: %f\ty: %f\n", v->x, v->y);
}

