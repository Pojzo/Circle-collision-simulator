#ifndef SIMULATION_H
#define SIMULATION_H
#include <SDL2/SDL.h>

SDL_Window *init_window();
SDL_Renderer *init_renderer(SDL_Window *window);
void refresh_screen(SDL_Renderer *renderer);
int handle_quit();

#endif
