#include <stdio.h>
#include "circle.h"
#include "config.h"
#include <math.h>

double floor(double num) {
    long long n = (long long)num;
    double d = (double)n;
    if (d == num || num >= 0)
        return d;
    else
        return d - 1;
}

// constructor for structure Circle
circle_t *circle_ctor (float pos_x_, float pos_y_, float radius_, int r_, int g_, int b_, int a_) {

    circle_t *circle = (circle_t *)malloc(sizeof(circle_t));
    
    // if malloc failed
    if (circle == NULL) {
        return circle;
    }

    circle->pos_x = pos_x_; // center x coordinate 
    circle->pos_y = pos_y_; // center y coordinate 
    circle->vel_x = 0; // x velocity
    circle->vel_y = 0; // y velocity
    circle->radius = radius_; // radius of circle
    circle->r = r_;
    circle->g = g_;
    circle->b = b_;
    circle->a = a_;

    return circle;
}

// draw circle to SDL_Renderer
// fill circle with specified color in constructor
void circle_draw (SDL_Renderer *r, circle_t *c) {
    // credit to https://gist.github.com/derofim/912cfc9161269336f722

    for (double dy = 1; dy <= c->radius; dy += 1.0)
    {
        double dx = floor(sqrt((2.0 * c->radius * dy) - (dy * dy)));
        SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
        SDL_RenderDrawLine(r, c->pos_x - dx, c->pos_y + dy - c->radius, c->pos_x + dx, c->pos_y + dy - c->radius);
        SDL_RenderDrawLine(r, c->pos_x - dx, c->pos_y - dy + c->radius, c->pos_x + dx, c->pos_y - dy + c->radius);
    }
}

// move circle by, restrain circle from leaving window
void circle_move (circle_t *c) {
    if (c->pos_x + c->vel_x > SCREEN_WIDTH - c->radius) {
        c->vel_x *= -1;
    }
    if (c->pos_x + c->vel_x < c->radius) {
        c->vel_x *= -1;
    }
    if (c->pos_y + c->vel_y > SCREEN_HEIGHT - c->radius) {
        c->vel_y *= -1;
    }
    if (c->pos_y + c->vel_y < c->radius) {
        c->vel_y *= -1;
    }

    c->pos_x += c->vel_x;
    c->pos_y += c->vel_y;
}

void circle_set_vel_x(circle_t *c, float vel_x_) {
    c->vel_x = vel_x_;
}

void circle_set_vel_y(circle_t *c, float vel_y_) {
    c->vel_y = vel_y_;
}

