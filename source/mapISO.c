#include "mapISO.h"
// the different levels will be saved in a text file
// where the lowest level is 0 and then if the room 
// name is "start" the first level will be called "start0"
// and the second level is "start1" etc.
MapLayer *createLayerOfMap(int Layer,char roomName[NAME],char fileName[NAME]){
    MapLayer *pMapLayer = malloc(sizeof(MapLayer));
    if (!pMapLayer) {
        fprintf(stderr, "Failed to allocate memory for Map Layer %d\n",Layer);
        return NULL;
    }
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapLayer->tileRect[y][x].w = ISO_TILE_SIZE;
            pMapLayer->tileRect[y][x].h = ISO_TILE_SIZE;     // isomtric 
            pMapLayer->tileRect[y][x].x = (int)((x - y) * ( ISO_TILE_SIZE/2));
            pMapLayer->tileRect[y][x].y = (int)(((x + y) * ( ISO_TILE_SIZE/4))-(Layer*ISO_TILE_SIZE/2));
        }
    }
    char localRomName[NAME];
    snprintf(localRomName, sizeof(localRomName), "%s%d", roomName, Layer);
    trimWhitespace(localRomName);
    strcpy(pMapLayer->roomLayerName,localRomName);
    redeFileForMap(pMapLayer->tileMap, fileName, localRomName);
    return pMapLayer;
}

Map *createMap(SDL_Renderer *pRenderer){
    Map *pMap = malloc(sizeof(Map));
    if(!pMap){
        fprintf(stderr,"Failde to allocate memory for Map\n");
        return NULL;
    }
    strcpy(pMap->curentRoom,"start");
    strcpy(pMap->mapFile,"resources/map.txt");

    pMap->TILE_SIZE_H = ISO_TILE_SIZE;
    pMap->TILE_SIZE_W = ISO_TILE_SIZE;
    SDL_Surface *tmpMap = IMG_Load("resources/ISO7Linus.png");
    if(!tmpMap){
        fprintf(stderr,"Error creating Surface for map, %s\n",IMG_GetError());
        return NULL;
    }
    pMap->pTileShet = SDL_CreateTextureFromSurface(pRenderer,tmpMap);
    SDL_FreeSurface(tmpMap);
    if(!pMap->pTileShet){
        fprintf(stderr,"Error creating Texture for map, %s\n",IMG_GetError());
        return NULL;
    }    
    pMap->tileIndex[0] = (SDL_Rect){0,0,64,64}; 
    pMap->tileIndex[1] = (SDL_Rect){64*1,0,64,64}; 
    pMap->tileIndex[2] = (SDL_Rect){64*2,0,64,64}; 
    pMap->tileIndex[3] = (SDL_Rect){64*3,0,64,64}; 
    pMap->tileIndex[4] = (SDL_Rect){0,64,64,64}; 
    pMap->tileIndex[5] = (SDL_Rect){64,64,64,64}; 
    pMap->tileIndex[6] = (SDL_Rect){64*2,64,64,64}; 
    pMap->tileIndex[7] = (SDL_Rect){64*3,64,64,64}; 
    return pMap;
}

void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            printf("%c",tileMap[y][x]);
            //printf("%d",tileMap);
        }
        printf("\n");
    }
}

void renderTile(SDL_Renderer *pRenderer,char tile,SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],
                SDL_Rect tileRect,SDL_Texture *pTileShet){
    switch (tile){
    case 'a':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[0],&tileRect);
        break;
    case 'b': 
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[1],&tileRect);
        break;
    case 'c':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        break;
    case 'd':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[3],&tileRect);
        break;    
    case 'e':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[4],&tileRect);
        break;
    case 'f':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[5],&tileRect);
        break;
    case 'g':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[6],&tileRect);
        break;
    case 'h':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[7],&tileRect);
        break;
    default:   
        //void (´ || a -1 )
        break;
    }
}

void renderMap(SDL_Renderer *pRenderer,char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],
                SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],SDL_Texture *pTileShet,
                SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int  x = 0; x < NUMMBER_OF_TILSE_X; x++){
        renderTile(pRenderer,tileMap[y][x],tileIndex,tileRect[y][x],pTileShet);
        }
        
    }
}

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRoom[]){
    char buffer[256];
    bool foundRoom = false;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Clude not open %s!\n",fileName);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        trimWhitespace(buffer); 
        if (strcmp(buffer, newRoom) == 0) {
            for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++) {
                for (int x = 0; x < NUMMBER_OF_TILSE_X; x++) {
                    fscanf(fp, " %c", &tileMap[y][x]);
                }
                trimWhitespace(tileMap[y]); 
            }
            foundRoom = true;
            break;
        }
    }
    if(!foundRoom){ // if no room is found lode an emty one
        for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
            for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
                tileMap[y][x] = '`';
            }
        }
    }
    fclose(fp);
}

void updatCurentMap(SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],int TILE_SIZE_W,int TILE_SIZE_H){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            tileRect[y][x].w = TILE_SIZE_W;
            tileRect[y][x].h = TILE_SIZE_H;     // isomtric
            tileRect[y][x].x = (int)(x - y) * (TILE_SIZE_W/2);
            tileRect[y][x].y = (int)(x + y) * (TILE_SIZE_H/4);
        }
    }
}