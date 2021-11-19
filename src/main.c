// // test
#include <SDL2/SDL.h>
#include <stdio.h>
#include "rect.h"
#include "circle.h"
#include "color.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_NAME "Window"

typedef SDL_Rect Rect;

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

    // set color for renderer as white
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

    // clear window, create a white background
    SDL_RenderClear (renderer);
     
    Rect r;
    rect_ctor (&r, 50, 50, 50, 50);

    // set color for renderer as white
    SDL_SetRenderDrawColor (renderer, 0, 0, 255, 255);
    circle_t c;
    const int c_x = SCREEN_WIDTH / 2;
    const int c_y = SCREEN_HEIGHT / 2;
    const int radius = 50;
    color_t color;
    color_ctor (&color, 0, 0, 255, 0);
    if (!circle_ctor(&c, c_x, c_y, radius, &color)) {
        printf ("Brasko nieco sa nepodarilo\n");
        return 1;
    }
    circle_draw (renderer, &c);

    //SDL_RenderFillRect (renderer, &r);
    SDL_RenderPresent (renderer);

    SDL_Delay (5000);
    SDL_DestroyWindow (window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
