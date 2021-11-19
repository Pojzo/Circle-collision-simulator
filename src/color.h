#ifndef COLOR_H
#define COLOR_H

typedef struct Color {
    int r; // red
    int g; // green
    int b; // blue
    int a; // alpha
} color_t;

int color_ctor (color_t *c, int r_, int g_, int b_, int a_);

#endif
