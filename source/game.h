#ifndef GAME_H
#define GAME_H

#include "map.h"

typedef struct{
    Init* pInit;
    Map* pMap;
    bool keys[SDL_NUM_SCANCODES];
    bool programIsRunning;
    SDL_Texture *helloworld;
    SDL_Rect hello;
    TTF_Font *font;
}Game;



#endif 