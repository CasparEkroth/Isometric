#ifndef MAP_H
#define MAP_H
#include "toolSDL.h"

#define  NUMMBER_OF_TILSE_Y 30
#define  NUMMBER_OF_TILSE_X 30
#define NUMMBER_OF_DIFFERENT_TILSE 10 


typedef struct{
    char map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Rect map_rect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    //
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];
    SDL_Texture* pTileShet; 
}Map;


#endif 