#ifndef MAPISO_H
#define MAPISO_H
#include "toolSDL.h"

#define  NUMMBER_OF_TILSE_Y 30
#define  NUMMBER_OF_TILSE_X 30
#define NUMMBER_OF_DIFFERENT_TILSE 10 
#define FILE_LENGTH 40 
#define TILE_SIZE 32
#define ISO_TILE_SIZE (TILE_SIZE*2)
#define DEPTH 2
typedef struct {
    char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];//pos
    char roomLayerName[NAME];
}MapLayer;
// skilnaden kommer vara ca -(1/2) i både x och y

typedef struct {
    int TILE_SIZE_W,TILE_SIZE_H;
    SDL_Texture *pTileShet;
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];//sprits
    char curentRoom[FILE_LENGTH];
    char mapFile[FILE_LENGTH];
    MapLayer *pTrueMap[DEPTH];
}Map;


Map *createMap(SDL_Renderer *pRenderre);
MapLayer *createLayerOfMap(int Level,char romName[NAME],char fileName[NAME]);

void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

void renderTile(SDL_Renderer *pRenderer,char tile,SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],
                SDL_Rect tileRect,SDL_Texture *pTileShet);

void renderMap(SDL_Renderer *pRenderer,char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],
                SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],SDL_Texture *pTileShet,
                SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRom[]);
void updatCurentMap(SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],int TILE_SIZE_W,int TILE_SIZE_H);


#endif 