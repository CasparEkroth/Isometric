#ifndef GAME_H
#define GAME_H

#include "mapISO.h"

typedef struct{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderer;
    Map* pMap;
    bool keys[SDL_NUM_SCANCODES];
    bool programIsRunning,isMakingMap;
}Game;

void input(SDL_Event event,Game* pGame);
void render(Game *pGame);

void gameCycel(Game *pGame,SDL_Event event);


#endif 