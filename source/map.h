#ifndef MAP_H
#define MAP_H
#include "toolSDL.h"

#define  NUMMBER_OF_TILSE_Y 30
#define  NUMMBER_OF_TILSE_X 30
#define NUMMBER_OF_DIFFERENT_TILSE 10 
#define FILE_LENGTH 40 
#define TILE_SIZE 32

typedef struct {
    int TILE_SIZE_W,TILE_SIZE_H;
    char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Texture *pTileShet;
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];//sprits
    SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];//pos
    char curentRoom[FILE_LENGTH];
    char mapFile[FILE_LENGTH];
}Map;


Map *createMap(SDL_Renderer *pRenderre);
void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

void renderTile(SDL_Renderer *pRenderer,char tile,SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],
                SDL_Rect tileRect,SDL_Texture *pTileShet);

void renderMap(SDL_Renderer *pRenderer,char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],
                SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],SDL_Texture *pTileShet,
                SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRom[]);
void updatCurentMap(SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],int TILE_SIZE_W,int TILE_SIZE_H);


#endif 