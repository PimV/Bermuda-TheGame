#pragma once
#include "header_loader.h"
#include <vector>
#include "Image.h"

using namespace std;

class ImageLoader
{
private:
	SDL_Renderer* renderer;
	vector<SDL_Texture*> tileSets;
	vector<Image*> images;

	//Interact Green/Red
	SDL_Texture* treeInteractTexture;
	SDL_Texture* treeCantInteractTexture;

	SDL_Texture* carrotInteractOverlay;

	SDL_Texture* rockInteractOverlay;
	SDL_Texture* rockCantInteractOverlay;

	SDL_Texture* cactusBigInteractOverlay;
	SDL_Texture* cactusBigCantInteractOverlay;
public:
	ImageLoader(SDL_Renderer* renderer);
	~ImageLoader();
	int loadTileset(string filename, double tileWidth, double tileHeight);
	int getCurrentImageCount();

	//Interact Green/Red
	SDL_Texture* getInteractTreeImage();
	SDL_Texture* getCantInteractTreeImage();

	SDL_Texture* getCarrotInteractImage();

	SDL_Texture* getInteractRockImage();
	SDL_Texture* getCantInteractRockImage();
	
	SDL_Texture* getInteractCactusBigImage();
	SDL_Texture* getCantInteractCactusBigImage();

	//SDL_Texture* loadSpriteSheet(string filename);
	Image* getMapImage(int tileID);
};
