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


Uint32 getPixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0]<<16 | p[1]<<8 | p[2];
            else
                return p[0] | p[1]<<8 | p[2]<<16;
        case 4:
            return *(Uint32 *)p;
    }
    return 0;
}

void RBG(SDL_Surface *surface, int x, int y){
    // Lås ytan innan vi läser (om den inte redan är låst)
    //x=x+(3*64); 
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
    printf("Pixel at (%d,%d) has RGBA = (r%u,g%u,b%u)\n", x, y, r, g, b);
    // Lås upp när klart
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

// Suppose 'isoRect' is the tile bounding box 
//   isoRect.x, isoRect.y is the *top-left* of that tile’s bounding box
//   isoRect.w, isoRect.h is the full width & height of the diamond
//
// We can compute the center of the diamond and do a quick diamond-shaped bounding check.
bool inDiamond(SDL_Rect isoRect, SDL_Point mouse){
    int halfW = isoRect.w / 2;
    int halfH = isoRect.h / 2;
    // Center of the isometric diamond
    int centerX = isoRect.x + halfW;
    int centerY = isoRect.y + halfH / 2; // because the tile’s “center” is halfway in Y

    // Distance from center
    int dx = abs(mouse.x - centerX);
    int dy = abs(mouse.y - centerY);

    // For an isometric diamond, 2*dy + dx <= halfW can be used as a quick test
    // or you can tune the shape by adjusting halfH, etc.

    // If the diamond is placed so that isoRect.h is actually twice its diamond’s “height,” 
    // you sometimes do:  if (dx <= halfW - (dy * (halfW / halfH)) ) ...

    // A commonly used approach is:
    if (dx * (halfH) + dy * (halfW) <= halfW * halfH) {
        return true;
    } else {
        return false;
    }
}
