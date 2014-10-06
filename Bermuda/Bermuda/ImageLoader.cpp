#include "ImageLoader.h"
#include <iostream>

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void ImageLoader::loadTileset(string filename, int tileWidth, int tileHeight)
{
	SDL_Texture* tileSet = IMG_LoadTexture(renderer, (RESOURCEPATH + filename).c_str());
	
	if (tileSet == nullptr)
	{
		std::cout << "Couldn't load " << RESOURCEPATH + filename << endl;
	}
	
	int x = 0;
	int y = 0;
	int fileWidth = 0;
	int fileHeight = 0;
	SDL_QueryTexture(tileSet, nullptr, nullptr, &fileWidth, &fileHeight);

	while ( y < fileHeight )
	{
		while ( x < fileWidth )
		{
			SDL_Rect* crop = new SDL_Rect();
			crop->x = x;
			crop->y = y;
			crop->w = tileWidth;
			crop->h = tileHeight;

			images.push_back(new Image(tileSet, crop));
			x += tileWidth;
		}
		x = 0;
		y += tileHeight;
	}
}

Image* ImageLoader::getMapImage(int tileID)
{
	return images.at(tileID-1);
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
