//utilitySDL
#ifndef TOOLSDL_H
#define TOOLSDL_H

#include "initSDL.h"

#define NAME 40

bool colitino(SDL_Rect A,SDL_Rect B);
bool pointInRect(SDL_Rect A, SDL_Point P);
void trimWhitespace(char *str);

SDL_Texture* makeStringInToSDL_Texture(char string[NAME], TTF_Font *pFont,SDL_Renderer* pRendererer);
SDL_Rect setingSizeOfStringToRect(char string[NAME],SDL_Point startingPoint,int h,int w);




#endif