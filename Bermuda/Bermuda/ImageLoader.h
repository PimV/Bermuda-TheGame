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
	SDL_Texture* canInteractTreeTexture;
	SDL_Texture* cantInteractTreeTexture;
	SDL_Texture* carrotInteractOverlay;

	SDL_Texture* rockInteractOverlay;
	SDL_Texture* rockCantInteractOverlay;
public:
	ImageLoader(SDL_Renderer* renderer);
	~ImageLoader();
	int loadTileset(string filename, double tileWidth, double tileHeight);
	int getCurrentImageCount();
	SDL_Texture* getInteractTreeImage();
	SDL_Texture* getCantInteractTreeImage();
	SDL_Texture* getCarrotInteractImage();

	SDL_Texture* getInteractRockImage();
	SDL_Texture* getCantInteractRockImage();

	//SDL_Texture* loadSpriteSheet(string filename);
	Image* getMapImage(int tileID);
};
