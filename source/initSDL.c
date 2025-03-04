#include "initSDL.h"

bool initialize_window(Game *pGame){ // Initialiserar SDL och skapar fönster
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0 || SDL_Init(SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "Error initializing SDL. %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fprintf(stderr,"SDL_mixer could not initialize! Mix_Error: %s\n",Mix_GetError());
        return false;
    }
    pGame->pWindow = SDL_CreateWindow(
        NULL, // Titel
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y 
        STARTING_WINDOW_WIDTH, 
        STARTING_WINDOW_HEIGHT, 
        SDL_WINDOW_RESIZABLE  // Flags
    );
    if (!pGame->pWindow) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    pGame->pRenderere = SDL_CreateRenderer(pGame->pWindow, -1, render_flags);
    if (!pGame->pRenderere) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }
    pGame->font = TTF_OpenFont("resources/Academy Engraved LET Fonts.ttf",24);
    if(!pGame->font){
        fprintf(stderr,"Error opening Font: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void close_SDL(SDL_Window* pWindow,SDL_Renderer *pRenderer, Game *pGame){
    if(pGame->font) TTF_CloseFont(pGame->font);
    if (pRenderer) SDL_DestroyRenderer(pRenderer);
    if (pWindow) SDL_DestroyWindow(pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void input(SDL_Event event,Game* pGame){
    while (SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_QUIT:
            pGame->programIsRunning = false;
            break;
        case SDL_KEYDOWN: 
            pGame->keys[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            pGame->keys[event.key.keysym.scancode] = false; 
        default:
            break;
        }
    }
    if(pGame->keys[SDL_SCANCODE_ESCAPE]) pGame->programIsRunning = false;
}

void render(Game *pGame){
    SDL_RenderClear(pGame->pRenderere);
    SDL_RenderCopy(pGame->pRenderere,pGame->helloworld,NULL,&pGame->hello);
    SDL_RenderPresent(pGame->pRenderere);
}

void update(Game *pGame){

}
