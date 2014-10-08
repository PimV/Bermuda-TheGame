#include "SDLInitializer.h"


SDLInitializer::SDLInitializer(void)
{
}


SDLInitializer::~SDLInitializer(void)
{
}

void SDLInitializer::init(const char* title, int width, int height, int bpp, bool fullscreen) {
	window = SDL_CreateWindow(
		title,
		640,
		480,
		width,
		height,
		0
		);
	//om ff te testen
	renderer = SDL_CreateRenderer(window, -1, 0);
}



void SDLInitializer::clearScreen() {
	SDL_RenderClear(renderer);
}

void SDLInitializer::drawTexture(SDL_Texture* texture, const SDL_Rect* destRect) {
	SDL_RenderCopy(renderer, texture, NULL,destRect);
}

void SDLInitializer::drawScreen() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLInitializer::getRenderer() {
	return renderer;
}