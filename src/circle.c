#include <stdio.h>
#include "circle.h"

// constructor for structure Circle
int circle_ctor (circle_t *c, int x_, int y_, int radius_, color_t *color_) {
    c->x = x_; // center x coordinate 
    c->y = y_; // center y coordinate 
    c->radius = radius_; // radius of circle
    c->color = color_;

    return 1;
}

void circle_draw (SDL_Renderer *r, circle_t *c) {
    for (int i = -c->radius; i <= c->radius; i++) {
        for (int j = -c->radius; j <= c->radius; j++) {
            if (i * i + j * j < c->radius * c->radius) {
                printf("Drawing point %d %d\n", i, j);
                SDL_RenderDrawPoint (r, c->x + i, c->y + j);
            }
        }
    }
}
