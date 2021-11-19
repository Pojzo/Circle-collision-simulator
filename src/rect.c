#include <stdio.h>
#include "rect.h"

int rect_ctor (Rect *r, int x_, int y_, int w_, int h_) {
    r->x = x_; 
    r->y = y_;
    r->w = w_;
    r->h = h_;

    return 1;
}
