#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    float x;
    float y;
} vector_t;

vector_t *vector_create(float x_, float y_);
float vector_dot_product(vector_t *first, vector_t *second);
vector_t *vector_multiply(vector_t* v, float x);
vector_t *vector_subtract(vector_t *first, vector_t *second);
void vector_free(vector_t *v);
void vector_print(vector_t *v);

#endif
