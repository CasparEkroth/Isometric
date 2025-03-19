#include "game.h"
#include "map_maker.h"

void removing(Game *pGame);
void initGame(Game *pGame);

int main(int argc, char **argv){
    Game g = {0};

    SDL_Event event;
    initGame(&g);
    for (int i = 0; i < DEPTH; i++) printMap(g.pMap->pTrueMap[i]->tileMap);
    while (g.programIsRunning){
        gameCycel(&g,event);
        if(g.isMakingMap){
            MapMaker *m = initMapMaker("resources/map.txt",g.pMap->TILE_SIZE_W,g.pMap->TILE_SIZE_H,"start",g.pRenderer);
            for (int i = 0; i < DEPTH; i++) m->pLayer[i] = createLayerOfMap(i,g.pMap->curentRoom,g.pMap->mapFile);
            for (int i = 0; i < DEPTH; i++)if(isOnListofRom(m->fileName,m->pLayer[i]->roomLayerName,&m->fileIdex[i])){}

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
    for (int i = 0; i < DEPTH; i++){
        pGame->pMap->pTrueMap[i] = createLayerOfMap(i,pGame->pMap->curentRoom,pGame->pMap->mapFile);
    }
}

void removing(Game *pGame){
    for (int i = 0; i < DEPTH; i++){
        if(pGame->pMap->pTrueMap[i]) free(pGame->pMap->pTrueMap[i]);
    }
    if(pGame->pMap->pTileShet) SDL_DestroyTexture(pGame->pMap->pTileShet);
    if(pGame->pMap) free(pGame->pMap);
}
