#pragma once
#include "header_loader.h"
#include "Image.h"
#include "Overlays.h"
#include <vector>
#include <map>

using namespace std;

class ImageLoader
{
private:
	SDL_Renderer* renderer;
	vector<SDL_Texture*> tileSets;
	vector<Image*> images;

	std::map<Overlays, SDL_Texture*> overlayImages;

public:
	ImageLoader(SDL_Renderer* renderer);
	int loadTileset(string filename, int tileWidth, int tileHeight);
	int getCurrentImageCount();

	void initOverlays();
	SDL_Texture* getOverLayImage(Overlays overlay);

	Image* getMapImage(int tileID);
	void cleanup();
	virtual ~ImageLoader();
};
