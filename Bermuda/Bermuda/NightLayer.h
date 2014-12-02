#pragma once
#include "header_loader.h"
#include "Camera.h"
#include "MainEntityContainer.h"

class NightLayer
{
public:
	NightLayer();
	virtual ~NightLayer();

	void draw(Camera *camera, MainEntityContainer* mec);
private:
	SDL_Surface* blackSurface;
	SDL_Surface* lightSourceImage;
	double alphaLevel;

	void calculateAlpha(SDL_Texture* texture);
	void drawLightSource(SDL_Surface* surface, SDL_Rect* screenRect, SDL_Rect* sourceRect, SDL_Rect* destRect);
};

