#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "circle.h"
#include "config.h"
#include "vector.h"

#define PI 3.141592654

#define abs(x) x > 0 ? x : -x

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
    // create vector for position
    circle->pos = vector_create(pos_x_, pos_y_);

    // create vector for velocity
    circle->vel = vector_create(0, 0);

    // create copy of vel 
    circle->next_vel = vector_create(pos_x_, pos_y_);
    circle->radius = radius_; // radius of circle

    circle->mass = CIRCLE_DEFAULT_MASS; // mass
    // colors 
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
        SDL_RenderDrawLine(r, c->pos->x - dx, c->pos->y + dy - c->radius, c->pos->x + dx, c->pos->y + dy - c->radius);
        SDL_RenderDrawLine(r, c->pos->x - dx, c->pos->y - dy + c->radius, c->pos->x + dx, c->pos->y - dy + c->radius);
    }
}

// move circle by, restrain circle from leaving window
void circle_move(circle_t *c) {
    c->vel->x = c->next_vel->x;
    c->vel->y = c->next_vel->y;
    if (c->pos->x + c->vel->x > SCREEN_WIDTH - c->radius) {
        if (c->vel->x > 0) {
            c->vel->x *= -1;
        }
    }
    if (c->pos->x + c->vel->x < c->radius) {
        if (c->vel->x < 0) {
            c->vel->x *= -1;
        }
    }
    if (c->pos->y + c->vel->y > SCREEN_HEIGHT - c->radius) {
        if (c->vel->y > 0) {
            c->vel->y *= -1;
        }
    }
    if (c->pos->y + c->vel->y < c->radius) {
        if (c->vel->y < 0) {
            c->vel->y *= -1;
        }
    }
    c->next_vel->x = c->vel->x;
    c->next_vel->y = c->vel->y;

    c->pos->x += c->vel->x;
    c->pos->y += c->vel->y;
}

// set x velocity of circle
void circle_set_vel_x(circle_t *c, float vel_x_) {
    c->vel->x = c->next_vel->x = vel_x_;
}

// set y velocity of circle
void circle_set_vel_y(circle_t *c, float vel_y_) {
    c->vel->y = c->next_vel->y = vel_y_;
}

// set mass of circle
void circle_set_mass(circle_t *c, float mass_) {
    if (mass_ >= CIRCLE_MIN_MASS && mass_ <= CIRCLE_MAX_MASS) {
        c->mass = mass_;
        return;
    }
    fprintf(stderr, "Mass is not in valid range\n");
}

// function that is called when two circles collide
void collide(circle_t *c1, circle_t *c2) {

    // https://flatredball.com/documentation/tutorials/math/circle-collision/
    double angle = atan2((c2->pos->y - c1->pos->y), (c2->pos->x - c1->pos->x));
    float distance_between_circles =
        (float)sqrt(
                (c2->pos->x - c1->pos->x) * (c2->pos->x - c1->pos->x) +
                (c2->pos->y - c1->pos->y) * (c2->pos->y - c1->pos->y));

    float distance_to_move = c1->radius + c2->radius - distance_between_circles;

    c2->pos->x += cos(angle) * distance_to_move;
    c2->pos->y += sin(angle) * distance_to_move;

    //https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Balls1.cpp

    float fDistance = c1->radius + c2->radius;

    // Normal
    float nx = (c2->pos->x - c1->pos->x) / fDistance;
    float ny = (c2->pos->y - c1->pos->y) / fDistance;

    // Tangent
    float tx = -ny;
    float ty = nx;

    // Dot Product Tangent
    float dpTan1 = c1->vel->x * tx + c1->vel->y * ty;
    float dpTan2 = c2->vel->x * tx + c2->vel->y * ty;

    // Dot Product Normal
    float dpNorm1 = c1->vel->x * nx + c1->vel->y * ny;
    float dpNorm2 = c2->vel->x * nx + c2->vel->y * ny;

    // Conservation of momentum in 1D
    float m1 = (dpNorm1 * (c1->mass - c2->mass) + 2.0 * c2->mass * dpNorm2) / (c1->mass + c2->mass);
    float m2 = (dpNorm2 * (c2->mass - c1->mass) + 2.0 * c1->mass * dpNorm1) / (c1->mass + c2->mass);

    // Update ball velocities
    c1->next_vel->x = tx * dpTan1 + nx * m1;
    c1->next_vel->y = ty * dpTan1 + ny * m1;

    c2->next_vel->x = tx * dpTan2 + nx * m2;
    c2->next_vel->y = ty * dpTan2 + ny * m2;
}
