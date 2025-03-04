#ifndef INITSDL_H
#define INITSDL_H

#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define STARTING_WINDOW_WIDTH 800 
#define STARTING_WINDOW_HEIGHT 600

#define VISIBLE_WINDOW_X 20
#define VISIBLE_WINDOW_Y 15 

typedef struct{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderer;
}Init;


bool initialize_window(Init *pInit);

void close_SDL(SDL_Window* pWindow,SDL_Renderer *pRenderer);


#endif