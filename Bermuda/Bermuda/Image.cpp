#include "Image.h"


Image::Image(SDL_Texture* tileSet, SDL_Rect* cropRect, double width, double height)
	: tileSet(tileSet), cropRect(cropRect), width(width), height(height)
{
}

SDL_Texture* Image::getTileSet()
{
	return tileSet;
}

SDL_Rect* Image::getCroppingRect()
{
	return cropRect;
}

double Image::getWidth()
{
	return width;
}

double Image::getHeight()
{
	return height;
}

Image::~Image()
{
	delete cropRect;
	cropRect = nullptr;

	SDL_DestroyTexture(tileSet);
	tileSet = nullptr;
}
