#include "map_maker.h"
//input 
//render 
//seving to file                                                                                //ta bort
MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH,char romeName[NAME]){
    MapMaker* pMapMaker = malloc(sizeof(MapMaker));
    if(!pMapMaker){
        fprintf(stderr,"Erorr alocating memory for MapMaker\n");
        return NULL;
    }
    for (int i = 0; i < DEPTH; i++) pMapMaker->fileIdex[i] = 0;

    pMapMaker->isChosingNewTile = false;
    pMapMaker->isMakingMap = true;
    pMapMaker->isSavede = false;
    strcpy(pMapMaker->fileName,fileName);
    strcpy(pMapMaker->romeName,romeName);

    pMapMaker->selectedLayer = 1;
    pMapMaker->zoom = 0;
    pMapMaker->visibleWindow.x = VISIBLE_WINDOW_X;
    pMapMaker->visibleWindow.y = VISIBLE_WINDOW_Y;
    pMapMaker->selectedTile = ('a'-1);
    pMapMaker->highlight_rect = (SDL_Point){0,0};
    pMapMaker->mapOfset = (SDL_Point){0,0};
    pMapMaker->mousePos = (SDL_Point){0,0};
    pMapMaker->ISOofSet = (SDL_Point){0,0};
    return pMapMaker;
} 

void maker(MapMaker *pMapMaker, Game *pGame,bool *isProgramRunnig){
    SDL_Event event;
    while (pMapMaker->isMakingMap){
        while (SDL_PollEvent(&event)){
            maker_input(pMapMaker,event,isProgramRunnig,pGame);
        }
        maker_update(pMapMaker,pGame->pWindow);
        maker_render(pGame->pRenderer,pMapMaker,pGame->pMap,event);
    }
    for (int i = 0; i < DEPTH; i++){
        saveMademap(pMapMaker->fileName,pMapMaker->fileIdex[i],pMapMaker->pLayer[i]->roomLayerName,
        pMapMaker->pLayer[i]->tileMap);
    }
    for (int i = 0; i < DEPTH; i++) if(pMapMaker->pLayer[i]) free(pMapMaker->pLayer[i]);
    free(pMapMaker);
}

void maker_render(SDL_Renderer *pRenderer,MapMaker *pMapMaker,Map *pMap,SDL_Event event){
    SDL_RenderClear(pRenderer);
    Uint32 mouseState = SDL_GetMouseState(&pMapMaker->mousePos.x,&pMapMaker->mousePos.y);
    if(pMapMaker->isChosingNewTile){
        SDL_Rect A ={32,32,32,32};
        for (int i = 0; i <NUMMBER_OF_DIFFERENT_TILSE; i++){
            renderTile(pRenderer,'a'+i,pMap->tileIndex,A,pMap->pTileShet);
            if(pointInRect(A,pMapMaker->mousePos)){
                SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
                SDL_RenderDrawRect(pRenderer, &A); 
                if(mouseState){
                    pMapMaker->selectedTile = ('a'+i);
                    pMapMaker->isChosingNewTile = false;
                }
            }
            A.x += 64;
            if(A.x > 64*10){
                A.x = 32;
                A.y += 64;
            }
        }
        //##########################
        //### välja lager // selsectetLayer
        //##########################
    }else{
        for (int i = 0; i < DEPTH; i++){
            renderMap(pRenderer,pMapMaker->pLayer[i]->tileMap,
            pMap->tileIndex,pMap->pTileShet,pMapMaker->pLayer[i]->tileRect);
        }        
        if (pMapMaker->highlight_rect.x < NUMMBER_OF_TILSE_X && pMapMaker->highlight_rect.y < NUMMBER_OF_TILSE_Y) {
            SDL_Rect tmp = pMapMaker->pLayer[pMapMaker->selectedLayer]->tileRect[pMapMaker->highlight_rect.y][pMapMaker->highlight_rect.x];
            tmp.h = tmp.h/2;
            SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[0],
            &pMapMaker->pLayer[pMapMaker->selectedLayer]->tileRect[pMapMaker->highlight_rect.y+pMapMaker->ISOofSet.y][pMapMaker->highlight_rect.x+pMapMaker->ISOofSet.x]);
        }
    }
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(pRenderer);
}

void maker_update(MapMaker *pMapMaker,SDL_Window *pWindow){
    for (int i = 0; i < DEPTH; i++){
        for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
            for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
                pMapMaker->pLayer[i]->tileRect[y][x].x += pMapMaker->mapOfset.x;
                pMapMaker->pLayer[i]->tileRect[y][x].y += pMapMaker->mapOfset.y;
            }
        }
    }
    if(pMapMaker->zoom != 0){
        int width, height;
        SDL_GetWindowSize(pWindow, &width, &height);
        pMapMaker->visibleWindow.x +=pMapMaker->zoom;
        pMapMaker->visibleWindow.y +=pMapMaker->zoom;
        width = width/pMapMaker->visibleWindow.x;
        height = height/pMapMaker->visibleWindow.y;
        for(int i = 0; i < DEPTH; i++)updatCurentMap(pMapMaker->pLayer[i]->tileRect,width,height);
    }
    pMapMaker->mapOfset =(SDL_Point){0,0};
    pMapMaker->zoom = 0;
}

void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isProgramRunnig,Game *pGame){
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    mouse.y -= 15;
    pMapMaker->mousePos = mouse;
    switch (event.type){
    case SDL_QUIT:
        pMapMaker->isMakingMap = false;
        *isProgramRunnig = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        pMapMaker->keys[event.button.state] = SDL_PRESSED;
        break;
    case SDL_MOUSEBUTTONUP:
        pMapMaker->keys[event.button.state] = SDL_RELEASED;
        break;
    case SDL_KEYDOWN:
        pMapMaker->keys[event.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        pMapMaker->keys[event.key.keysym.scancode] = false;
        break;
    default:
        break;
    }
    static int ode = 0;
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            //if(++ode%2==1){
                SDL_Rect tileBox = pMapMaker->pLayer[pMapMaker->selectedLayer]->tileRect[y][x];
                // Instead of halving tileBox.h, do a diamond test:
                if (inDiamond(tileBox, mouse)) {
                    // That means we clicked inside tile (x,y)
                    pMapMaker->highlight_rect.x = x;
                    pMapMaker->highlight_rect.y = y;
                }
            //}
            
        }
    }
    if(mouseState)pMapMaker->pLayer[pMapMaker->selectedLayer]->
    tileMap[pMapMaker->highlight_rect.y+pMapMaker->ISOofSet.y][pMapMaker->highlight_rect.x+pMapMaker->ISOofSet.x] 
    = pMapMaker->selectedTile;
    if(pMapMaker->keys[SDL_SCANCODE_ESCAPE]){
        pMapMaker->isMakingMap = false;
        *isProgramRunnig = false;
    }
    if(pMapMaker->keys[SDL_SCANCODE_UP]) pMapMaker->mapOfset.y = SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_DOWN]) pMapMaker->mapOfset.y -= SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_LEFT]) pMapMaker->mapOfset.x = SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_RIGHT]) pMapMaker->mapOfset.x -= SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_N]) pMapMaker->isChosingNewTile = true;
    if(pMapMaker->keys[SDL_SCANCODE_RETURN]) pMapMaker->isChosingNewTile = false;
    if(pMapMaker->keys[SDL_SCANCODE_V]) pMapMaker->selectedTile = ('a'-1);
    if(pMapMaker->keys[SDL_SCANCODE_P]) pMapMaker->zoom = -1; 
    if(pMapMaker->keys[SDL_SCANCODE_M]) pMapMaker->zoom = 1; 
    if(pMapMaker->keys[SDL_SCANCODE_P]){
        if (SDL_GetWindowFlags(pGame->pWindow) & SDL_WINDOW_FULLSCREEN){
            SDL_SetWindowFullscreen(pGame->pWindow, 0);  // Switch back to windowed mode
        }else{
            SDL_SetWindowFullscreen(pGame->pWindow, SDL_WINDOW_FULLSCREEN);  // Fullscreen mode
        }
        resizeWindow(pMapMaker,pGame->pMap,pGame->pWindow);
    } 
    if(pMapMaker->keys[SDL_SCANCODE_0]) pMapMaker->selectedLayer = 0;
    if(pMapMaker->keys[SDL_SCANCODE_1]) pMapMaker->selectedLayer = 1;
}

//added changes so that the isometric levels are also saved
void saveMademap(char fileName[],int fileIdex,char roomNameL[],char map[][NUMMBER_OF_TILSE_X]){
    FILE *fp = fopen(fileName, "r");// något blir fel arayen skjut åt ett håll
    if (!fp) {
        fprintf(stderr, "Error: Could not open %s for reading!\n",fileName);
        return;
    }
    FILE *tmp = fopen("tmp.txt", "w");
    if (!tmp) {
        fprintf(stderr, "Error: Could not open tmp.txt for writing!\n");
        fclose(fp);
        return;
    }
    char buffer[256];
    int count = 0;
    int skipCondition = fileIdex;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        if(count == skipCondition){
            for (int i = 0; i < NUMMBER_OF_TILSE_Y; i++){
                fgets(buffer, sizeof(buffer), fp);
            }
            break;
        }
        trimWhitespace(buffer);
        fprintf(tmp,"%s\n",buffer);
        count++;
    }
    trimWhitespace(roomNameL);
    fprintf(tmp,"%s\n",roomNameL);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            fprintf(tmp,"%c",map[y][x]);
        }
        fprintf(tmp,"\n");
    }
    while (fgets(buffer,sizeof(buffer),fp) != NULL){
        trimWhitespace(buffer);
        fprintf(tmp,"%s\n",buffer);
    }
    
    fclose(fp);
    fclose(tmp);

    remove(fileName);
    rename("tmp.txt",fileName);
}

bool isOnListofRom(char fileName[NAME],char romName[NAME],int *fileIndex){
    char buffer[256];
    int contRom = 0,line = 0;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Clude not open %s!\n",fileName);
        return NULL;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        trimWhitespace(buffer);
        if(strcmp(buffer,romName) == 0){
            fclose(fp);
            *fileIndex = line;
            printf("%d line ",*fileIndex);
            return true;
        }
        line++;
    }
    fclose(fp);
    return false;
}

void resizeWindow(MapMaker *pMapMaker, Map *pMap,SDL_Window *pWindow){
    int width, height;
    SDL_GetWindowSize(pWindow, &width, &height);
    int tmp = width/VISIBLE_WINDOW_X;
    pMap->TILE_SIZE_W = tmp;
    int tmp1 = height/VISIBLE_WINDOW_Y;
    pMap->TILE_SIZE_H = tmp1;
    for(int i = 0; i < DEPTH; i++)updatCurentMap(pMapMaker->pLayer[i]->tileRect,pMap->TILE_SIZE_W,pMap->TILE_SIZE_H);
}


