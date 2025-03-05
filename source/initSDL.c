#include "initSDL.h"

bool initialize_window(SDL_Window **ppWindow, SDL_Renderer **ppRenderer){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0 || SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return false;
    }
    SDL_Window *win = SDL_CreateWindow(
        "Isometric",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        STARTING_WINDOW_WIDTH,
        STARTING_WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    if (!win) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, render_flags);
    if (!ren) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        return false;
    }

    // If we got here, everything is fine:
    *ppWindow = win;  // Now it sets the caller's pointer
    *ppRenderer = ren; //  ...
    return true;
}


void close_SDL(SDL_Window* pWindow,SDL_Renderer *pRenderer){
    if (pRenderer) SDL_DestroyRenderer(pRenderer);
    if (pWindow) SDL_DestroyWindow(pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
