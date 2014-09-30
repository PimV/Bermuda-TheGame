#include "SDLInitializer.h"


SDLInitializer::SDLInitializer(void)
{
	init("Bermuda", 640, 480, 0, false);


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

void SDLInitializer::drawTexture(SDL_Texture* texture) {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL,NULL);
	SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLInitializer::getRenderer() {
	return renderer;
}