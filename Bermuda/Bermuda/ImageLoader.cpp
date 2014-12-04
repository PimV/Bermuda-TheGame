#include "ImageLoader.h"
#include <iostream>

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

//Returns the first ID of the new tileset images
int ImageLoader::loadTileset(string filename, int tileWidth, int tileHeight)
{
	int startID = images.size() + 1;
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
	int drawWidth = tileWidth;
	int drawHeight = tileHeight;

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
	return startID;
}

/*SDL_Texture* ImageLoader::loadSpriteSheet(string filename)
{
	SDL_Texture* spriteSheet = IMG_LoadTexture(renderer, (RESOURCEPATH + filename).c_str());

	if (spriteSheet == nullptr)
		std::cout << "Couldn't load " << RESOURCEPATH + filename << endl;

	return spriteSheet;
}*/

int ImageLoader::getCurrentImageCount()
{
	return images.size();
}

Image* ImageLoader::getMapImage(int tileID)
{
	size_t sTileId = tileID;

	if(tileID > 0 && sTileId <= images.size())
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
	for (size_t i = 0; i < images.size(); i++)
	{
		delete images.at(i);
	}

	// Destroy all tilesets
	for (size_t i = 0; i < tileSets.size(); i++)
	{
		SDL_DestroyTexture(tileSets.at(i));
	}
}
