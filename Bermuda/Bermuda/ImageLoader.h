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
public:
	ImageLoader(SDL_Renderer* renderer);
	~ImageLoader();
	int loadTileset(string filename, double tileWidth, double tileHeight);
	int getCurrentImageCount();
	//SDL_Texture* loadSpriteSheet(string filename);
	Image* getMapImage(int tileID);
};
