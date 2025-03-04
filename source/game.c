#include "game.h"

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