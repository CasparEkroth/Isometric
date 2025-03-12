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
//the combination of the two above functions
SDL_Texture* textToScreen(char string[NAME], TTF_Font *pFont,SDL_Renderer *pRendrerer,SDL_Rect *pRect);

void addIntToString(char str[NAME], int X);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void RBG(SDL_Surface *surface, int x, int y);
bool inDiamond(SDL_Rect isoRect, SDL_Point mouse);





#endif