#include <stdio.h>
#include "circle.h"
#include "config.h"

// constructor for structure Circle
int circle_ctor (circle_t *c, int pos_x_, int pos_y_, int radius_, color_t *color_) {
    c->pos_x = pos_x_; // center x coordinate 
    c->pos_y = pos_y_; // center y coordinate 
    c->vel_x = 0; // x velocity
    c->vel_y = 0; // y velocity
    c->radius = radius_; // radius of circle
    c->color = color_;

    return 1;
}

// draw circle to SDL_Renderer
// fill circle with specified color in constructor
void circle_draw (SDL_Renderer *r, circle_t *c) {
    SDL_SetRenderDrawColor (r, c->color->r, c->color->g, c->color->b, c->color->a);
    for (int i = -c->radius; i <= c->radius; i++) {
        for (int j = -c->radius; j <= c->radius; j++) {
            if (i * i + j * j < c->radius * c->radius) {
                SDL_RenderDrawPoint (r, c->pos_x + i, c->pos_y + j);
            }
        }
    }
}

// move circle by, restrain circle from leaving window
void circle_move (circle_t *c) {
    if (c->pos_x + c->vel_x > SCREEN_WIDTH) {
        c->vel_x *= -1;
    }
    if (c->pos_x + c->vel_x < 0) {
        c->vel_x *= -1;
    }
    if (c->pos_y + c->vel_y > SCREEN_HEIGHT) {
        c->vel_y *= -1;
    }
    if (c->pos_y + c->vel_y < 0) {
        c->vel_y *= -1;
    }
    c->pos_x += c->vel_x;
    c->pos_y += c->vel_y;
}
