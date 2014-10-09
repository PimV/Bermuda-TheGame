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
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		fullscreen
		);
	renderer = SDL_CreateRenderer(window, -1, 0);
	//TODO: Willen we dit wel gebruiken? Beetje buggy. Soms last van artifacting en seems. Vanaf 1920x900 geen correcte aspect ratio (tenzij full-screen)
	SDL_RenderSetLogicalSize(renderer, 1600, 900);
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