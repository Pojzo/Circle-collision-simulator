#ifndef SIMULATION_H
#define SIMULATION_H
#include <SDL2/SDL.h>
#include "circle.h"

SDL_Window *init_window();
SDL_Renderer *init_renderer(SDL_Window *window);
void refresh_screen(SDL_Renderer *renderer);
int handle_quit();
void detect_collision(circle_t **circles, int num_circles);

#endif
