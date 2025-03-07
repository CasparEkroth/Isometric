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
    if(isOnListofRom(fileName,romeName,&pMapMaker->fileIdex)){
        pMapMaker->isNewRoom = false;
        redeFileForMap(pMapMaker->map,fileName,romeName);
    }else{
        pMapMaker->isNewRoom = true;
        for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
            for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
                pMapMaker->map[y][x] = ('a'-1);
            }
        }
    }
    pMapMaker->isChosingNewTile = false;
    pMapMaker->isMakingMap = true;
    pMapMaker->isSavede = false;
    strcpy(pMapMaker->fileName,fileName);
    strcpy(pMapMaker->romeName,romeName);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapMaker->rect_map[y][x].w = tileSizeW;
            pMapMaker->rect_map[y][x].h = tileSizeH;    //isometric
            pMapMaker->rect_map[y][x].x = (int)(x - y) * ( tileSizeW/2);
            pMapMaker->rect_map[y][x].y = (int)(x + y) * ( tileSizeH/4);
        }
    }
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
    saveMademap(pMapMaker);
    free(pMapMaker);
}

void maker_render(SDL_Renderer *pRenderer,MapMaker *pMapMaker,Map *pMap,SDL_Event event){
    SDL_RenderClear(pRenderer);
    Uint32 mouseState = SDL_GetMouseState(&pMapMaker->mousePos.x,&pMapMaker->mousePos.y);
    if(pMapMaker->isChosingNewTile){
        SDL_Rect A ={32,32,32,32};
        for (int i = 0; i <NUMMBER_OF_DIFFERENT_TILSE; i++){
            //SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[i],&A);
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
    }else{
        renderMap(pRenderer,pMapMaker->map,pMap->tileIndex,pMap->pTileShet,pMapMaker->rect_map);
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
        if (pMapMaker->highlight_rect.x < NUMMBER_OF_TILSE_X && pMapMaker->highlight_rect.y < NUMMBER_OF_TILSE_Y) {
            SDL_Rect tmp = pMapMaker->rect_map[pMapMaker->highlight_rect.y][pMapMaker->highlight_rect.x];
            tmp.h = tmp.h/2;
            SDL_RenderDrawRect(pRenderer, &tmp);
            SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[0],
            &pMapMaker->rect_map[pMapMaker->highlight_rect.y+pMapMaker->ISOofSet.y][pMapMaker->highlight_rect.x+pMapMaker->ISOofSet.x]);
        }
    }
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(pRenderer);
}

void maker_update(MapMaker *pMapMaker,SDL_Window *pWindow){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapMaker->rect_map[y][x].x += pMapMaker->mapOfset.x;
            pMapMaker->rect_map[y][x].y += pMapMaker->mapOfset.y;
        }
    }
    if(pMapMaker->zoom != 0){
        int width, height;
        SDL_GetWindowSize(pWindow, &width, &height);
        pMapMaker->visibleWindow.x +=pMapMaker->zoom;
        pMapMaker->visibleWindow.y +=pMapMaker->zoom;
        width = width/pMapMaker->visibleWindow.x;
        height = height/pMapMaker->visibleWindow.y;
        updatCurentMap(pMapMaker->rect_map,width,height);
    }
    pMapMaker->mapOfset =(SDL_Point){0,0};
    pMapMaker->zoom = 0;
}

void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isProgramRunnig,Game *pGame){
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
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
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            SDL_Rect tmp2 = pMapMaker->rect_map[y][x];
            tmp2.h = tmp2.h/2;
            if(pointInRect(tmp2,mouse)){
                SDL_Point ofSet = getISOofSet(pGame->pMap->pTileSurface,mouse.x%pGame->pMap->TILE_SIZE_W,
                    mouse.y%(pGame->pMap->TILE_SIZE_H/2));
                //inIsometricRect(pMapMaker->rect_map[y][x],mouse);
                pMapMaker->ISOofSet.x = ofSet.x;
                pMapMaker->ISOofSet.y = ofSet.y;
                pMapMaker->highlight_rect.x = x;
                pMapMaker->highlight_rect.y = y;
                break;
            }
        }
    }
    if(mouseState)pMapMaker->map[pMapMaker->highlight_rect.y+pMapMaker->ISOofSet.y][pMapMaker->highlight_rect.x+pMapMaker->ISOofSet.x] = pMapMaker->selectedTile;
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
}

void saveMademap(MapMaker *pMapMaker){
    FILE *fp = fopen(pMapMaker->fileName, "r");// något blir fel arayen skjut åt ett håll
    if (!fp) {
        fprintf(stderr, "Error: Could not open %s for reading!\n", pMapMaker->fileName);
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
    int skipCondition = pMapMaker->fileIdex;
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
    fprintf(tmp,"%s\n",pMapMaker->romeName);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            fprintf(tmp,"%c",pMapMaker->map[y][x]);
        }
        fprintf(tmp,"\n");
    }
    while (fgets(buffer,sizeof(buffer),fp) != NULL){
        trimWhitespace(buffer);
        fprintf(tmp,"%s\n",buffer);
    }
    
    fclose(fp);
    fclose(tmp);

    remove(pMapMaker->fileName);
    rename("tmp.txt", pMapMaker->fileName);
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
    updatCurentMap(pMapMaker->rect_map,pMap->TILE_SIZE_W,pMap->TILE_SIZE_H);
}

/*
SDL_Point inIsometricRect(SDL_Rect A,SDL_Point mouse){// 0 inuti rätt -+ fel
    SDL_Point ofSet ={0,0};
    if(mouse.y>=A.y+(A.h/4)){
        if(mouse.x>=A.x+(A.w/2)){
            if(mouse.y>=((A.y+(A.h/2))-(mouse.x*2))){
            ofSet = (SDL_Point){1,0};
            }else ofSet = (SDL_Point){0,0};
        }else {
            if(mouse.y>=((A.y+(A.h/4))+(mouse.x*2))){
            ofSet = (SDL_Point){0,1};
            }else ofSet = (SDL_Point){0,0};
        }
    }else{
        if(mouse.x>=A.x+(A.w/2)){
                        if(mouse.y<=((A.y)-(mouse.x*2))){
            ofSet = (SDL_Point){0,-1};
            }else ofSet = (SDL_Point){0,0};
        }else{
            if(mouse.y<=((A.y+(A.h/4))-(mouse.x*2))){
            ofSet = (SDL_Point){-1,0};
            }else ofSet = (SDL_Point){0,0};
        }
    }
    return ofSet;
}
*/

SDL_Point getISOofSet(SDL_Surface *surface, int x, int y){
    // Lås ytan innan vi läser (om den inte redan är låst)
    x=x+(3*64); 
    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) < 0) {
            fprintf(stderr, "Can't lock surface: %s\n", SDL_GetError());
        }
    }
    
    // Hämta själva pixelvärdet (RGBA packat i en Uint32)
    Uint32 pixel = getPixel(surface, x, y);
    
    // Konvertera till R, G, B, A
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

    // Lås upp när klart
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
    SDL_Point ofSet = {0,0};
    if(g>128 && b>128 && r>128) return ofSet;
    printf("Pixel at (%d,%d) has RGBA = (r%u,g%u,b%u)\n", x, y, r, g, b);
    if(r>128) ofSet =(SDL_Point){-1,0};
    if(g>128) ofSet =(SDL_Point){0,-1};
    if(b>128) ofSet =(SDL_Point){1,0};
    if(g>128 && b>128) ofSet =(SDL_Point){0,1};
    return ofSet;
}