#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"
#include <SDL2/SDL.h>

typedef struct Circle {
    int pos_x;
    int pos_y;
    int vel_x;
    int vel_y;
    int radius;
    color_t *color;
} circle_t;

int circle_ctor (circle_t *c, int pos_x_, int pos_y_, int radius_, color_t *color_);
void circle_draw (SDL_Renderer *r, circle_t *c);
void circle_move (circle_t *c);

#endif
