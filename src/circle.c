#include <stdio.h>
#include <math.h>
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

    circle->pos_x = pos_x_; // center x coordinate 
    circle->pos_y = pos_y_; // center y coordinate 
    circle->vel_x = 0; // x velocity
    circle->vel_y = 0; // y velocity
    circle->radius = radius_; // radius of circle

    circle->mass = DEFAULT_CIRCLE_MASS; // mass
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

// set x velocity of circle
void circle_set_vel_x(circle_t *c, float vel_x_) {
    c->vel_x = vel_x_;
}

// set y velocity of circle
void circle_set_vel_y(circle_t *c, float vel_y_) {
    c->vel_y = vel_y_;
}

// function that is called when two circles collide
void collide(circle_t *c1, circle_t *c2) {
    printf("Circle1->pos_x: %f\n", c1->pos_x);
    printf("Circle1->pos_y: %f\n", c1->pos_y);
    printf("Circle2->pos_x: %f\n", c2->pos_x);
    printf("Circle2->pos_y: %f\n", c2->pos_y);

    printf("Circle1->vel_x: %f\n", c1->vel_x);
    printf("Circle1->vel_y: %f\n", c1->vel_y);
    printf("Circle2->vel_x: %f\n", c2->vel_x);
    printf("Circle2->vel_y: %f\n", c2->vel_y);

    double angle = atan2((c2->pos_y - c1->pos_y), (c2->pos_x - c1->pos_x));
    float distance_between_circles =
        (float)sqrt(
                (c2->pos_x - c1->pos_x) * (c2->pos_x - c1->pos_x) +
                (c2->pos_y - c1->pos_y) * (c2->pos_y - c1->pos_y));
    
    float distance_to_move = c1->radius + c2->radius - distance_between_circles;
    //(void)distance_to_move;
    //(void)angle;
    printf("Angle: %f\n", angle);
    printf("Distance between circles: %f\n", distance_between_circles);
    printf("Distance to move: %f\n", distance_to_move);

   
    vector_t *tangent_vector = vector_create((c2->pos_y - c1->pos_y) / 1000, -(c2->pos_x - c1->pos_x) / 1000);
    vector_t *relative_velocity = vector_create(c1->vel_x - c2->vel_x, c1->vel_y - c2->vel_y);

    //printf("%f %f %f %f\n", c1->vel_x, c1->vel_y, c2->vel_x, c2->vel_y);
    
   // vector_print(tangent_vector);
    printf("Tangent vector: ");
    vector_print(tangent_vector);
    printf("Relative velocity: : ");
    vector_print(relative_velocity);
    
    
    float length = vector_dot_product(relative_velocity, tangent_vector);

    printf("Length: %f\n", length);

    vector_t *velocity_component_on_tangent = vector_multiply(tangent_vector, length);
    vector_t *velocity_component_perpendicular_to_tangent = vector_subtract(relative_velocity, velocity_component_on_tangent);

    printf("Velocity component on tangent: ");
    vector_print(velocity_component_on_tangent);
    printf("Velocity velocity component perpendicular to tangent");
    vector_print(velocity_component_perpendicular_to_tangent);

    printf("--------------------------------------------\n");


    c2->pos_x += cos(angle) * distance_to_move;
    c2->pos_y += sin(angle) * distance_to_move;

    c1->vel_x -= velocity_component_perpendicular_to_tangent->x;
    c1->vel_y -= velocity_component_perpendicular_to_tangent->y;

    c2->vel_x += velocity_component_perpendicular_to_tangent->x;
    c2->vel_y += velocity_component_perpendicular_to_tangent->y;

    //vector_free(tangent_vector);
    //vector_free(relative_velocity);
    //vector_free(velocity_component_on_tangent);
    //vector_free(velocity_component_perpendicular_to_tangent);

    /*
       float temp_x = circle->vel_x;
       float temp_y = circle->vel_y;

       circle->vel_x = collider->vel_x;
       circle->vel_y = collider->vel_y;


       collider->vel_x = temp_x;
       collider->vel_y = temp_y;

       circle->vel_x = (circle->vel_x * (circle->mass - collider->mass) + (2 * collider->mass * collider->vel_x) / (circle->mass + collider->mass));
       circle->vel_y = (circle->vel_y * (circle->mass - collider->mass) + (2 * collider->mass * collider->vel_y) / (circle->mass + collider->mass));

       collider->vel_x = (collider->vel_x * (collider->mass - circle->mass) + (2 * circle->mass * circle->vel_x) / (collider->mass + circle->mass));
       collider->vel_y = (collider->vel_y * (collider->mass - circle->mass) + (2 * circle->mass * circle->vel_y) / (collider->mass + circle->mass));
       */
}
