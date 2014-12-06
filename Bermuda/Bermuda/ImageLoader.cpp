#include "ImageLoader.h"
#include <iostream>

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

//Returns the first ID of the new tileset images
int ImageLoader::loadTileset(string filename, double tileWidth, double tileHeight)
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
	double drawWidth = tileWidth;
	double drawHeight = tileHeight;

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

int ImageLoader::getCurrentImageCount()
{
	return images.size();
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

void ImageLoader::cleanup()
{
	// Destroy all images
	for (int i = 0; i < images.size(); i++)
	{
		delete images[i];
		images[i] = nullptr;
	}
	std::vector<Image*>().swap(images); //Clear and shrink vector

	// Destroy all tilesets
	for (int i = 0; i < tileSets.size(); i++)
	{
		SDL_DestroyTexture(tileSets[i]);
		tileSets[i] = nullptr;
	}
	std::vector<SDL_Texture*>().swap(tileSets); //Clear and shrink vector
}

ImageLoader::~ImageLoader()
{
	this->cleanup();
}
