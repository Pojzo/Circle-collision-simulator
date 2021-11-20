#include <stdio.h>
#include "circle.h"
#include "color.h"
#include "simulation.h"
#include "config.h"

int main(int argc, char **argv) {
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

    refresh_screen(renderer); // make background white
    circle_t *circle;  // test circle
    color_t *color_blue; // Color object with blue color

    color_blue = color_ctor(0, 0, 255, 255); // constructor for blue color
    circle = circle_ctor((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2, 50, color_blue); // constructor for circle
    circle_set_vel_x(circle, 5); // set x velocity of circle to 5
    circle_set_vel_y(circle, 5); // set y velocity of circle to 5


    for (;;) {
        refresh_screen(renderer);
        circle_move(circle); // move circle with its velocity
        circle_draw(renderer, circle); // draw circle to screen
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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return renderer;
}

// refresh background to white
void refresh_screen(SDL_Renderer *renderer) {
    // set color for renderer as white
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);

    // clear window, create a white background
    SDL_RenderClear (renderer);
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
