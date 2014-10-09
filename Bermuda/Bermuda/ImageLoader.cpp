#include "ImageLoader.h"
#include <iostream>

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void ImageLoader::loadTileset(string filename, double tileWidth, double tileHeight)
{
	SDL_Texture* tileSet = IMG_LoadTexture(renderer, (RESOURCEPATH + filename).c_str());
	tileSets.push_back(tileSet);

	if (tileSet == nullptr)
	{
		std::cout << "Couldn't load " << RESOURCEPATH + filename << endl;
	}
	
	int x = 0;
	int y = 0;
	int fileWidth = 0;
	int fileHeight = 0;
	SDL_QueryTexture(tileSet, nullptr, nullptr, &fileWidth, &fileHeight);
	double drawWidth = tileWidth * (ScreenHeight / OPTIMALRESOLUTIONH);
	double drawHeight = tileHeight * (ScreenHeight / OPTIMALRESOLUTIONH);
	cout << (ScreenHeight / OPTIMALRESOLUTIONH) << endl;

	while ( y < fileHeight )
	{
		while ( x < fileWidth )
		{
			SDL_Rect* crop = new SDL_Rect();
			crop->x = x;
			crop->y = y;
			crop->w = tileWidth;
			crop->h = tileHeight;

			images.push_back(new Image(tileSet, crop, drawWidth, drawHeight));
			x += tileWidth;
		}
		x = 0;
		y += tileHeight;
	}
}

SDL_Texture* ImageLoader::loadSpriteSheet(string filename)
{
	SDL_Texture* spriteSheet = IMG_LoadTexture(renderer, (RESOURCEPATH + filename).c_str());

	if (spriteSheet == nullptr)
		std::cout << "Couldn't load " << RESOURCEPATH + filename << endl;

	return spriteSheet;
}

Image* ImageLoader::getMapImage(int tileID)
{
	if(tileID > 0 && tileID <= images.size())
	{
		return images.at(tileID-1);
	}
	else 
	{
		return nullptr;
	}
}

ImageLoader::~ImageLoader()
{
	// Destroy all images
	for (int i = 0; i < images.size(); i++)
	{
		delete images.at(i);
	}

	// Destroy all tilesets
	for (int i = 0; i < tileSets.size(); i++)
	{
		SDL_DestroyTexture(tileSets.at(i));
	}
}
