#include "toolSDL.h"

bool colitino(SDL_Rect A,SDL_Rect B){
    if(A.x + A.w >= B.x && 
        A.x <= B.x + B.w &&
        A.y + A.h >= B.y &&
        A.y <= B.y + B.h){
        return true;
    }else{
        return false;
    }
}

bool pointInRect(SDL_Rect A, SDL_Point P){
    if (P.x >= A.x && 
        P.x <  A.x + A.w && 
        P.y >= A.y && 
        P.y <  A.y + A.h){
        return true;
    }
    return false;
}

void trimWhitespace(char *str) {// Ta bort extra whitespace
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

SDL_Rect setingSizeOfStringToRect(char string[NAME],SDL_Point startingPoint,int h,int w){
    SDL_Rect rect;
    rect.x =startingPoint.x * w;
    rect.y =startingPoint.y * h;
    rect.h = h;
    rect.w = ((w/2) *strlen(string));
    return rect;
}

SDL_Texture* makeStringInToSDL_Texture(char string[NAME], TTF_Font *pFont,SDL_Renderer* pRendererer){
    char stringBuff[128];
    snprintf(stringBuff,sizeof(stringBuff),"%s",string);
    SDL_Color color ={255,255,255,255};
    SDL_Surface* pSolidString = TTF_RenderText_Solid(pFont,stringBuff,color);
    SDL_Texture* pTextureString = SDL_CreateTextureFromSurface(pRendererer,pSolidString);
    SDL_FreeSurface(pSolidString);
    return pTextureString;
}