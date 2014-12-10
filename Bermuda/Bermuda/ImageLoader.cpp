#include "ImageLoader.h"
#include <iostream>
#include "GameStateManager.h"

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->initOverlays();
}

void ImageLoader::initOverlays()
{
	overlayImages[Overlays::cactusBig] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusBig_canInteract.png").c_str());
	overlayImages[Overlays::cactusBigCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusBig_cantInteract.png").c_str());
	overlayImages[Overlays::cactusSmall] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusSmall_canInteract.png").c_str());
	overlayImages[Overlays::cactusSmallCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusSmall_cantInteract.png").c_str());
	overlayImages[Overlays::carrot] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\carrot_canInteract.png").c_str());
	overlayImages[Overlays::fish] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\fish_canInteract.png").c_str());
	overlayImages[Overlays::fishCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\fish_cantInteract.png").c_str());
	overlayImages[Overlays::rock] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\rock_canInteract.png").c_str());
	overlayImages[Overlays::rockCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\rock_cantInteract.png").c_str());
	overlayImages[Overlays::spike] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\spikes_canInteract.png").c_str());
	overlayImages[Overlays::spikeCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\spikes_cantInteract.png").c_str());
	overlayImages[Overlays::treePine] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treePine_canInteract.png").c_str());
	overlayImages[Overlays::treePineCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treePine_cantInteract.png").c_str());
	overlayImages[Overlays::treeRound] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treeRound_canInteract.png").c_str());
	overlayImages[Overlays::treeRoundCant] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treeRound_cantInteract.png").c_str());
	overlayImages[Overlays::branch] = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\branch_canInteract.png").c_str());
}

SDL_Texture* ImageLoader::getOverLayImage(Overlays overlay)
{
	return this->overlayImages[overlay];
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

void ImageLoader::cleanup()
{
	// Destroy all images
	for (size_t i = 0; i < images.size(); i++)
	{
		delete images[i];
		images[i] = nullptr;
	}
	std::vector<Image*>().swap(images); //Clear and shrink vector

	// Destroy all tilesets
	for (size_t i = 0; i < tileSets.size(); i++)
	{
		SDL_DestroyTexture(tileSets[i]);
		tileSets[i] = nullptr;
	}
	std::vector<SDL_Texture*>().swap(tileSets); //Clear and shrink vector

	//Delete all overlay images
	typedef std::map<Overlays, SDL_Texture*>::iterator it_type;
	for(it_type iterator = this->overlayImages.begin(); iterator != this->overlayImages.end(); iterator++) {
		SDL_DestroyTexture(iterator->second);
		iterator->second = nullptr;
	}
}

ImageLoader::~ImageLoader()
{
	this->cleanup();
}
