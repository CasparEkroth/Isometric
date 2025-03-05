#include "game.h"
#include "map_maker.h"

void removing(Game *pGame);
void initGame(Game *pGame);

int main(void){
    Game g = {0};
    //MapMaker *m = {0};
    SDL_Event event;
    if(initialize_window(g.pInit)){
    g.programIsRunning = true;
    }else g.programIsRunning = false;

    while (g.programIsRunning){
        gameCycel(&g,event);
        if(g.isMakingMap){

        }
    }
    removing(&g);
    close_SDL(g.pInit->pWindow,g.pInit->pRenderer);
    return 0;
}

void initGame(Game *pGame){
    pGame->isMakingMap = false;
    pGame->pMap = createMap(pGame->pInit->pRenderer);
}

void removing(Game *pGame){
    if(pGame->pMap) free(pGame->pMap);
}
