#ifndef MAP_MAKER_H
#define MAP_MAKER_H
#include "game.h"

#define NR_OF_ROMS 3
#define SPEED (32)
#define ZOOM 10
#define NAME 40


typedef struct {
    char selectedTile;
    int fileIdex[DEPTH];
    int zoom;
    SDL_Point highlight_rect,visibleWindow;
    SDL_Point mapOfset,mousePos,ISOofSet;
    char fileName[NAME];
    char romeName[NAME];
    //char map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    //SDL_Rect rect_map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    MapLayer *pLayer[DEPTH];
    int selectedLayer;
    bool isSavede,isChosingNewTile,isMakingMap;
    bool keys[SDL_NUM_SCANCODES];
}MapMaker;


MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH,char romeName[NAME]);
//initialize the map maker 

bool isOnListofRom(char fileName[NAME],char romName[NAME],int *fileIndex);
//cheks if it is a new rom and gives the fileIndex, so we can save the new rom

void maker(MapMaker *pMapMaker, Game *pGame,bool *isProgramRunnig);
// the main funtionen that handels all of the inportent stuff

void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isProgramRunnig,Game *pGame);

// tacks the inputs to make chenges

void maker_update(MapMaker *pMapMaker,SDL_Window *pWindow);
// only movs the map

void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap,SDL_Event event);
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