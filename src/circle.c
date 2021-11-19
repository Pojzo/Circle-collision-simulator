#include <stdio.h>
#include "circle.h"

// constructor for structure Circle
int circle_ctor (circle_t *c, int x_, int y_, int radius_) {
    c->x = x_; // center x coordinate 
    c->y = y_; // center y coordinate 
    c->radius = radius_; // radius of circle

    return 1;

    }
