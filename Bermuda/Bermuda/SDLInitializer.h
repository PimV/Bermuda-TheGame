#pragma once
#include "header_loader.h"
#include <SDL_ttf.h>
class SDLInitializer
{
public:
	SDLInitializer(void);
	void init(const char* title, int width, int height, int bpp, bool fullscreen);
	void clearScreen();
	void drawTexture(SDL_Texture* texture,  const SDL_Rect* destRect,SDL_Rect* crop);
	void drawRect(SDL_Rect rect);
	void drawScreen();
	void drawText(std::string msg, int x, int y, int w, int h);
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	virtual ~SDLInitializer(void);
private:
	SDL_Surface* screen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

};

