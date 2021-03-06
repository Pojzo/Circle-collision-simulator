#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include "vector.h"

typedef struct Circle {
    vector_t *pos;
    vector_t *vel;
    vector_t *next_vel;
    float radius;
    float mass;
    int r;
    int g;
    int b;
    int a;
} circle_t;

circle_t  *circle_ctor (float pos_x_, float pos_y_, float radius_, int r_, int g_, int b_, int a_);
void circle_draw (SDL_Renderer *r, circle_t *c);
void circle_move (circle_t *c);
void circle_set_vel_x(circle_t *c, float vel_x_);
void circle_set_vel_y(circle_t *c, float vel_y_);
void circle_set_mass(circle_t *c, float mass);
void collide(circle_t* circle, circle_t* collider);

#endif
