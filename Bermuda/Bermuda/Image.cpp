#include "Image.h"


Image::Image(SDL_Texture* tileSet, SDL_Rect* cropRect)
{
	this->tileSet = tileSet;
	this->cropRect = cropRect;
}

SDL_Texture* Image::getTileSet()
{
	return tileSet;
}

SDL_Rect* Image::getCroppingRect()
{
	return cropRect;
}

Image::~Image()
{
	delete cropRect;
}
