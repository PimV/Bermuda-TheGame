#include "Image.h"
#include <iostream>

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
	//std::cout << "Cleaning Image" << std::endl;
	//std::cout << "    - Cleaning cropRect" << std::endl;
	delete cropRect;
	cropRect = nullptr;
	//std::cout << "Image cleaned" << std::endl;
}
