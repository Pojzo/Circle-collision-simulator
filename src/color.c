#include <stdio.h>
#include "color.h"

#define COLOR_MAX 255
#define COLOR_MIN 0

// basic colors 
color_t COLOR_RED = {.r = 255, .g = 0, .b = 0, .a = 255};
color_t COLOR_GREEN = {.r = 0, .g = 255, .b = 0, .a = 255};
color_t COLOR_BLUE = {.r = 0, .g = 0, .b = 255, .a = 255};

// constructor for struct Color
int color_ctor (color_t *c, int r_, int g_, int b_, int a_) {
    // variables have to be in range COLOR_MIN - COLOR_MAX
    if (r_ < COLOR_MIN || r_ > COLOR_MAX) {
        fprintf (stderr, "RGB value must be in range 0 - 255");
        return 0; 
    }

    if (g_ < COLOR_MIN || b_ > COLOR_MAX) {
        fprintf (stderr, "RGB value must be in range 0 - 255");
        return 0; 
    }

    if (b_ < COLOR_MIN || b_ > COLOR_MAX) {
        fprintf (stderr, "RGB value must be in range 0 - 255");
        return 0; 
    }

    if (a_ < COLOR_MIN || a_ > COLOR_MAX) {
        fprintf (stderr, "RGB value must be in range 0 - 255");
        return 0; 
    }
    // assign rgba valuesj
    c->r = r_;
    c->g = g_;
    c->b = b_;
    c->a = a_;

    return 1;
}

// export color constants
extern color_t COLOR_RED;
extern color_t COLOR_GREEN;
extern color_t COLOR_BLUE;
