#pragma once
#include "header_loader.h"

class Image
{
private:
	SDL_Texture* tileSet;
	SDL_Rect* cropRect;
public:
	Image(SDL_Texture* tileSet, SDL_Rect* cropRect);
	~Image();
	SDL_Texture* getTileSet();
	SDL_Rect* getCroppingRect();
};

