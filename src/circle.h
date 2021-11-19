#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"

typedef struct Circle {
    int x;
    int y;
    int radius;
    color_t *color;
} circle_t;

int circle_ctor (circle_t *c, int x_, int y_, int radius_);

#endif
