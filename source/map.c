#include "map.h"

Map *createMap(SDL_Renderer *pRenderre){
    Map *pMap = malloc(sizeof(Map));
    strcpy(pMap->curentRoom,"start");
    stpcpy(pMap->mapFile,"resourses/mapFile.txt");

    pMap->TILE_SIZE_H = TILE_SIZE;
    pMap->TILE_SIZE_W = TILE_SIZE;

    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMap->tileRect[y][x].w = pMap->TILE_SIZE_W;
            pMap->tileRect[y][x].h = pMap->TILE_SIZE_H;     // fix isomtric
            pMap->tileRect[y][x].x = (x * pMap->TILE_SIZE_W);
            pMap->tileRect[y][x].y = (y * pMap->TILE_SIZE_H);
        }
    }
    redeFileForMap(pMap->tileMap,pMap->mapFile,pMap->curentRoom);
    SDL_Surface *tmpMap = IMG_Load("resources/isometric_tile.png");
    if(!tmpMap){
        fprintf(stderr,"Error creating Surface for map, %s\n",IMG_GetError());
        return NULL;
    }
    pMap->pTileShet = SDL_CreateTextureFromSurface(pRenderre,tmpMap);
    SDL_FreeSurface(tmpMap);
    if(!pMap->pTileShet){
        fprintf(stderr,"Error creating Texture for map, %s\n",IMG_GetError());
        return NULL;
    }
    pMap->tileIndex[0] = (SDL_Rect){80,80,16,16}; 
    pMap->tileIndex[1] = (SDL_Rect){80,96,16,16}; 
    pMap->tileIndex[2] = (SDL_Rect){80,64,16,16}; 
    pMap->tileIndex[3] = (SDL_Rect){101,16,16,16}; 
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

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRom[]){
    char buffer[256];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Clude not open %s!\n",fileName);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        trimWhitespace(buffer); 
        if (strcmp(buffer, newRom) == 0) {
            for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++) {
                for (int x = 0; x < NUMMBER_OF_TILSE_X; x++) {
                    fscanf(fp, " %c", &tileMap[y][x]);
                }
                trimWhitespace(tileMap[y]);
            }
            break;
        }
    }
    fclose(fp);
}

void updatCurentMap(SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],int TILE_SIZE_W,int TILE_SIZE_H){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            tileRect[y][x].w = TILE_SIZE_W;
            tileRect[y][x].h = TILE_SIZE_H;     
            tileRect[y][x].x = (x * TILE_SIZE_W);
            tileRect[y][x].y = (y * TILE_SIZE_H);
        }
    }
}