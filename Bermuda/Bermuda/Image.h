#pragma once
#include "header_loader.h"

class Image
{
private:
	SDL_Texture* tileSet;
	SDL_Rect* cropRect;
	double width;
	double height;
public:
	Image(SDL_Texture* tileSet, SDL_Rect* cropRect, double width, double height);
	virtual ~Image();
	SDL_Texture* getTileSet();
	SDL_Rect* getCroppingRect();
	double getWidth();
	double getHeight();
};

