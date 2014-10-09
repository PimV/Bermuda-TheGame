#pragma once
#include "header_loader.h"
class SDLInitializer
{
public:
	SDLInitializer(void);
	void init(const char* title, int width, int height, int bpp, bool fullscreen);
	void clearScreen();
	void drawTexture(SDL_Texture* texture,  const SDL_Rect* destRect,SDL_Rect* crop);
	void drawScreen();
	SDL_Renderer* getRenderer();
	virtual ~SDLInitializer(void);
private:
	SDL_Surface* screen;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

