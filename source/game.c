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
    if(pGame->keys[SDL_SCANCODE_F]) pGame->isMakingMap = true;
}

void render(Game *pGame){
    SDL_RenderClear(pGame->pRenderer);
    for (int i = 0; i < DEPTH; i++){
        renderMap(pGame->pRenderer,pGame->pMap->pTrueMap[i]->tileMap,pGame->pMap->tileIndex,pGame->pMap->pTileShet,
        pGame->pMap->pTrueMap[i]->tileRect);
    }
    SDL_RenderPresent(pGame->pRenderer);
}

void gameCycel(Game *pGame,SDL_Event event){
    input(event,pGame);
    //update(pGame); not in use
    render(pGame);
}