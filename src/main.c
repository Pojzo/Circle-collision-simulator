// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <stdio.h>
#include "rect.h"

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

    const int radius = 50;
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i * i + j * j < radius * radius) {
                printf("Drawing point %d %d\n", i, j);
                SDL_RenderDrawPoint (renderer, i, j);
            }
        }
    }

    // render rect
    SDL_RenderFillRect (renderer, &r);

    /// render rect to the screen
    SDL_RenderPresent (renderer);

    SDL_Delay (5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
