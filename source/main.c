#include "game.h"
#include "map_maker.h"

void helloWorld(char str[NAME],Game *pGame);

int main(void){
    Game g = {0};
    //MapMaker *m = {0};
    SDL_Event event;
    if(initialize_window(&g)){
    g.programIsRunning = true;
    }else g.programIsRunning = false;

    while (g.programIsRunning){
        input(event,&g);
        update(&g);
        render(&g);
    }

    close_SDL(g.pInit->pWindow,g.pInit->pRenderer);

    return 0;
}

void helloWorld(char str[NAME],Game *pGame){
    pGame->hello = (SDL_Rect){5,5,50,50};
    SDL_Point A = (SDL_Point){pGame->hello.x,pGame->hello.y};
    pGame->hello= setingSizeOfStringToRect(str,A,pGame->hello.h,pGame->hello.w);
    pGame->helloworld = makeStringInToSDL_Texture(str,pGame->font,pGame->pInit->pRenderer);
}