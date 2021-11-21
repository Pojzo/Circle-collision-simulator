#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulation.h"
#include "config.h"
#include "time.h"

#define abs(a) a > 0 ? a : -a

int main(int argc, char **argv) {
    srand(time(NULL));
    (void)argc;
    (void)argv;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // initializewindow
    window = init_window();
    
    if (window == NULL) {
        fprintf(stderr, "Could not create window.\n");
        return 1;
    }
    
    // initialize renderer
    renderer = init_renderer(window);

    if (renderer == NULL) {
        fprintf(stderr, "Could not create renderer.\n");
        return 1;
    }

    const int num_circles = 10;
    const int radius = 30;
    circle_t *circles[num_circles];  // test circle
    for (int i = 0; i < num_circles; i++) {
        circle_t *circle;
        circle = circle_ctor((i + 1) * radius * 2 + 20, i * radius * 2 + 20, radius, rand() % 255, rand() % 255, rand() % 255, 255); // constructor for circle
        circle_set_vel_x(circle, rand() % 10); // set x velocity of circle to 5
        circle_set_vel_y(circle, rand() % 10); // set y velocity of circle to 5
        circles[i] = circle;
    }
    
    for (;;) {
        refresh_screen(renderer);
        for (int i = 0; i < num_circles; i++) {
            detect_collision(circles, num_circles);
            circle_move(circles[i]); // move circle with its velocity
            circle_draw(renderer, circles[i]); // draw circle to screen
        }
        SDL_RenderPresent(renderer); //
        SDL_Delay(DELAY_MS); // add delay between frames

        if (handle_quit()) { // if user pressed close button, handle quit returns 1
            printf ("Terminating program\n");
            SDL_DestroyWindow (window);
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }
}

// constructor for SDL_Window
// WINDOW_NAME is stored in config.h
SDL_Window *init_window() {
    SDL_Window *window = SDL_CreateWindow(
            WINDOW_NAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );

    return window;
}

// constructor for SDL_Renderer
SDL_Renderer *init_renderer(SDL_Window *window) {
    // create an instance of renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//SDL_RENDERER_ACCELERATED 
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    return renderer;
}

// refresh background to white
void refresh_screen(SDL_Renderer *renderer) {
    // set color for renderer as white
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);

    // clear window, create a white background
    SDL_RenderClear(renderer);
}

// returns true if user has pressed quit button
int handle_quit() {
    SDL_Event evt;
    while(SDL_PollEvent(&evt) != 0) {
        switch (evt.type) {
            case SDL_QUIT:    
                return 1;
        }
    }
    return 0;
}

// detect collision between circles
void detect_collision(circle_t **circles, int num_circles) {
    float diff_x; // x difference between centres of circles
    float diff_y; // y difference between centres of circles
    float distance; // euclidian distance between centres of circles
    float minimum_distance;

    for (int i = 0; i < num_circles; i++) {
        for (int j = 0; j < num_circles; j++) {
            if (i == j) {
                continue;
            }
            diff_x = abs(circles[i]->pos_x - circles[j]->pos_x);
            diff_y = abs(circles[i]->pos_y - circles[j]->pos_y);
            distance = diff_x * diff_x + diff_y * diff_y; // use pythagoeran therom to calculate distance
            minimum_distance = (circles[i]->radius + circles[j]->radius) * (circles[i]->radius + circles[j]->radius);

            if (distance < minimum_distance) { // if the distance is smalle
                // reverese velocities of both circles
                collide(circles[i], circles[j]);
            }
        }
    }
}

/*
// function adds a circle to simulation, without ovelapping with already added ones
int add_circle(circle_t **circles) {
return 1;
}
*/
