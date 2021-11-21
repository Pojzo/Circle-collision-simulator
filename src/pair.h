#ifndef PAIR_H
#define PAIR_H

typedef struct Pair {
    float x;
    float y;
} pair_t;

pair_t *create_pair(float x_, float y_);

#endif
