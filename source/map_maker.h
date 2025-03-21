#ifndef MAP_MAKER_H
#define MAP_MAKER_H
#include "game.h"

#define NR_OF_ROMS 3
#define SPEED (32)
#define ZOOM 10
#define NAME 40
#define NR_OF_STRINGS 8

typedef struct {
    char selectedTile;
    int fileIdex[DEPTH];
    int zoom;
    SDL_Point highlight_rect,visibleWindow;
    SDL_Point mapOfset,mousePos,ISOofSet;
    char fileName[NAME];
    char romeName[NAME];
    MapLayer *pLayer[DEPTH];
    int selectedLayer;
    bool isSavede,isChosingNewTile,isMakingMap,infoOpen;
    bool keys[SDL_NUM_SCANCODES];
    TTF_Font *pFont; 
    SDL_Texture *strings[NR_OF_STRINGS];
    SDL_Rect stringPos[NR_OF_STRINGS];
}MapMaker;

typedef enum MyEnumTag{ // index for the strings   
    CURENT_LEYER = 0,
    INPUT_V = 1,
    INPUT_P = 2,
    INPUT_M = 3,
    INPUT_N = 4,
    INPUT_L = 5,
    INPUT_ENTER = 6,
    INPUT_ESCAPE =7,
}MyEnumTag;

MapMaker* initMapMaker(char fileName[NAME],char romeName[NAME],SDL_Renderer *pRenderer);
//initialize the map maker 

bool isOnListofRom(char fileName[NAME],char romName[NAME],int *fileIndex);
//cheks if it is a new rom and gives the fileIndex, so we can save the new rom

void maker(MapMaker *pMapMaker, Game *pGame,bool *isProgramRunnig);
// the main funtionen that handels all of the inportent stuff

void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isProgramRunnig,Game *pGame);

// tacks the inputs to make chenges

void maker_update(MapMaker *pMapMaker,SDL_Window *pWindow);
// only movs the map

void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap);
//render

//void saveMademap(MapMaker *pMapMaker);
void saveMademap(char fileName[],int fileIdex,char roomNameL[],char map[][NUMMBER_OF_TILSE_X]);

//savse the map by rewrhitning the hole thing 

void resizeWindow(MapMaker *pMapMaker, Map *pMap,SDL_Window *pWindow);


#endif
//#######################################################################################
//#########     DOKUMETINTON       ######################################################
//#######################################################################################
// what do you need to use this file 
// [file for the maps]
// [bool for the game and the program]
// [SDL_window,SDL_renderer]
//###################################
// you will need a functioning system får rendering the map and the tiles individuali 
// that means also having a SDL_Texture for the tilemap and Rest for the spirits
// there are also a couple of other functions that you will need
//#######################################################################################