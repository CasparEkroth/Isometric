#include "game.h"
#include "map_maker.h"

void removing(Game *pGame);
void initGame(Game *pGame);

int main(void){
    Game g = {0};

    SDL_Event event;
    initGame(&g);
    printMap(g.pMap->tileMap);
    while (g.programIsRunning){
        gameCycel(&g,event);
        if(g.isMakingMap){
            MapMaker *m = initMapMaker("resources/map.txt",g.pMap->TILE_SIZE_W,g.pMap->TILE_SIZE_H,"start");
            maker(m,&g,&g.programIsRunning);
            g.isMakingMap = false;
        }
    }
    removing(&g);
    close_SDL(g.pWindow,g.pRenderer);
    return 0;
}

void initGame(Game *pGame){
    if(initialize_window(&pGame->pWindow,&pGame->pRenderer)){
    pGame->programIsRunning = true;
    }else pGame->programIsRunning = false;
    pGame->isMakingMap = false;
    pGame->pMap = createMap(pGame->pRenderer);
}

void removing(Game *pGame){
    if(pGame->pMap->pTileShet) SDL_DestroyTexture(pGame->pMap->pTileShet);
    if(pGame->pMap) free(pGame->pMap);
}
