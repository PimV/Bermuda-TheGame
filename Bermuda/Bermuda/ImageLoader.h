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

	SDL_Texture* treePineInteractTexture;
	SDL_Texture* treePineCantInteractTexture;

	SDL_Texture* carrotInteractOverlay;

	SDL_Texture* rockInteractOverlay;
	SDL_Texture* rockCantInteractOverlay;
	
	SDL_Texture* spikeInteractOverlay;
	SDL_Texture* spikeCantInteractOverlay;

	SDL_Texture* cactusBigInteractOverlay;
	SDL_Texture* cactusBigCantInteractOverlay;

	SDL_Texture* cactusSmallInteractOverlay;
	SDL_Texture* cactusSmallCantInteractOverlay;
	
	SDL_Texture* fishInteractOverlay;
	SDL_Texture* fishCantInteractOverlay;
public:
	ImageLoader(SDL_Renderer* renderer);
	~ImageLoader();
	int loadTileset(string filename, int tileWidth, int tileHeight);
	int getCurrentImageCount();

	//Interact Green/Red
	SDL_Texture* getInteractTreeImage();
	SDL_Texture* getCantInteractTreeImage();

	SDL_Texture* getInteractTreePineImage();
	SDL_Texture* getCantInteractTreePineImage();

	SDL_Texture* getInteractCarrotImage();

	SDL_Texture* getInteractRockImage();
	SDL_Texture* getCantInteractRockImage();

	SDL_Texture* getInteractSpikeImage();
	SDL_Texture* getCantInteractSpikeImage();
	
	SDL_Texture* getInteractCactusBigImage();
	SDL_Texture* getCantInteractCactusBigImage();

	SDL_Texture* getInteractCactusSmallImage();
	SDL_Texture* getCantInteractCactusSmallImage();
	
	SDL_Texture* getInteractFishImage();
	SDL_Texture* getCantInteractFishImage();

	//SDL_Texture* loadSpriteSheet(string filename);
	Image* getMapImage(int tileID);
};
