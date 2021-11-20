#include <SDL2/SDL.h>
#include <stdio.h>
#include "rect.h"
#include "circle.h"
#include "color.h"
#include "config.h"

const char *WINDOW_NAME = "Circles";

typedef SDL_Rect Rect;

void refresh_screen (SDL_Renderer *renderer);
int handle_quit();

int main(int argc, char **args) {
    (void) argc;
    (void) args;
    SDL_Window* window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
            WINDOW_NAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // setup rendere
    SDL_Renderer* renderer = NULL;

    // create an instance of renderer
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
    refresh_screen (renderer);
    
    Rect r;
    rect_ctor (&r, 50, 50, 50, 50);

    // set color for renderer as white
    circle_t c;
    const float c_x = (float)SCREEN_WIDTH / 2;
    const float c_y = (float)SCREEN_HEIGHT / 2;
    const float radius = 50;

    color_t color;
    color_ctor (&color, 0, 0, 255, 0);

    if (!circle_ctor(&c, c_x, c_y, radius, &color)) {
        printf ("Brasko nieco sa nepodarilo\n");
        return 1;
    }
    c.vel_x = 5;
    c.vel_y = 5;

    // main loop
    for (;;) {
        refresh_screen (renderer);
        circle_draw (renderer, &c);
        SDL_RenderPresent (renderer);
        SDL_Delay (DELAY_MS);
        circle_move (&c);

        if (handle_quit()) {
            printf ("Terminating program\n");
            SDL_DestroyWindow (window);
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }
}

void refresh_screen (SDL_Renderer *renderer) {
    // set color for renderer as white
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

    // clear window, create a white background
    SDL_RenderClear (renderer);
}

int handle_quit () {
    SDL_Event evt;
    while(SDL_PollEvent(&evt) != 0) {
        switch (evt.type) {
            case SDL_QUIT:    
                return 1;
        }
    }
    return 0;
}
