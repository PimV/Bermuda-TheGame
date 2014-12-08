#include "ImageLoader.h"
#include <iostream>
#include "GameStateManager.h"

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

SDL_Texture* ImageLoader::getInteractTreeImage() {
	if (treeInteractTexture == nullptr) {
		treeInteractTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treeRound_canInteract.png").c_str());
	}
	return treeInteractTexture;
}

SDL_Texture* ImageLoader::getCantInteractTreeImage() {
	if (treeCantInteractTexture == nullptr) {

		treeCantInteractTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treeRound_cantInteract.png").c_str());
	}
	return treeCantInteractTexture;
}

SDL_Texture* ImageLoader::getInteractTreePineImage() {
	if (treePineInteractTexture == nullptr) {
		treePineInteractTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treePine_canInteract.png").c_str());
	}
	return treePineInteractTexture;
}
SDL_Texture* ImageLoader::getCantInteractTreePineImage() {
	if (treePineCantInteractTexture == nullptr) {

		treePineCantInteractTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\treePine_cantInteract.png").c_str());
	}
	return treePineCantInteractTexture;
}

SDL_Texture* ImageLoader::getInteractCarrotImage() {
	if (carrotInteractOverlay == nullptr) {
		carrotInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\carrot_canInteract.png").c_str());
	}
	return carrotInteractOverlay;
}

SDL_Texture* ImageLoader::getInteractRockImage() {
	if (rockInteractOverlay == nullptr) {
		rockInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\rock_canInteract.png").c_str());
	}
	return rockInteractOverlay;
}

SDL_Texture* ImageLoader::getCantInteractRockImage() {
	if (rockCantInteractOverlay == nullptr) {
		rockCantInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\rock_cantInteract.png").c_str());
	}
	return rockCantInteractOverlay;
}

SDL_Texture* ImageLoader::getInteractSpikeImage() {
	if (spikeInteractOverlay == nullptr) {
		spikeInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\spikes_canInteract.png").c_str());
	}
	return spikeInteractOverlay;
}

SDL_Texture* ImageLoader::getCantInteractSpikeImage() {
	if (spikeCantInteractOverlay == nullptr) {
		spikeCantInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\spikes_cantInteract.png").c_str());
	}
	return spikeCantInteractOverlay;
}

SDL_Texture* ImageLoader::getInteractCactusBigImage() {
	if (cactusBigInteractOverlay == nullptr) {
		cactusBigInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusBig_canInteract.png").c_str());
	}
	return cactusBigInteractOverlay;
}

SDL_Texture* ImageLoader::getCantInteractCactusBigImage() {
	if (cactusBigCantInteractOverlay == nullptr) {
		cactusBigCantInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusBig_cantInteract.png").c_str());
	}
	return cactusBigCantInteractOverlay;
}

SDL_Texture* ImageLoader::getInteractCactusSmallImage() {
	if (cactusSmallInteractOverlay == nullptr) {
		cactusSmallInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusSmall_canInteract.png").c_str());
	}
	return cactusSmallInteractOverlay;
}

SDL_Texture* ImageLoader::getCantInteractCactusSmallImage() {
	if (cactusSmallCantInteractOverlay == nullptr) {
		cactusSmallCantInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\cactusSmall_cantInteract.png").c_str());
	}
	return cactusSmallCantInteractOverlay;
}

SDL_Texture* ImageLoader::getInteractFishImage() {
	if (fishInteractOverlay == nullptr) {
		fishInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\fish_canInteract.png").c_str());
	}
	return fishInteractOverlay;
}

SDL_Texture* ImageLoader::getCantInteractFishImage() {
	if (fishCantInteractOverlay == nullptr) {
		fishCantInteractOverlay = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Objects\\Overlay\\fish_cantInteract.png").c_str());
	}
	return fishCantInteractOverlay;
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
}

ImageLoader::~ImageLoader()
{
	this->cleanup();
}
