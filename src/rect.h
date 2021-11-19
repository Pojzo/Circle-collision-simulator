#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>

typedef SDL_Rect Rect;

int rect_ctor (Rect *r, int x_, int y_, int w_, int h_);


#endif
