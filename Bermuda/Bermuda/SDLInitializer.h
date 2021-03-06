#pragma once
#include "header_loader.h"
#include <SDL_ttf.h>
class SDLInitializer
{
public:
	SDLInitializer();
	void init(const char* title, int width, int height, int bpp, bool fullscreen);
	void clearScreen();
	void drawTexture(SDL_Texture* texture,  const SDL_Rect* destRect, SDL_Rect* crop);
	void drawScreen();

	void drawText(std::string msg, int x, int y, int w, int h, int fontSize = -1, int r = 255, int g = 255, int b = 255);
	void setRenderDrawColor(int r, int g, int b);
	void resetRenderDrawColor();

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	virtual ~SDLInitializer();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
};

