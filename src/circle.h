#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"
#include <SDL2/SDL.h>

typedef struct Circle {
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float radius;
    color_t *color;
} circle_t;

int circle_ctor (circle_t *c, float pos_x_, float pos_y_, float radius_, color_t *color_);
void circle_draw (SDL_Renderer *r, circle_t *c);
void circle_move (circle_t *c);

#endif
