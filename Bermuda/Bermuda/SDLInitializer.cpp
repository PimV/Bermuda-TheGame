#include "SDLInitializer.h"
#include <iostream>


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
	
	//Initialize SDL2_ttf
	TTF_Init();


	//TODO: Willen we dit wel gebruiken? Beetje buggy. Veel last van screen tearing en seems.
	//SDL_RenderSetLogicalSize(renderer, 1600, 900);
}

void SDLInitializer::drawText(std::string msg, int x, int y, int w, int h) {
	font = TTF_OpenFont((RESOURCEPATH + "fonts\\segoeuib.ttf").c_str(), h);

	SDL_Surface* imgTxt;
	SDL_Rect txtRect;
	SDL_Color fColor;

	txtRect.x = x;
	txtRect.y = y;
	txtRect.w = msg.length() * h / 3;
	txtRect.h = h;

	fColor.r = fColor.g = fColor.b = 245;
	imgTxt = TTF_RenderText_Blended(font, msg.c_str(), fColor);

	SDL_Texture* imgTxture = SDL_CreateTextureFromSurface(this->getRenderer(), imgTxt);

	SDL_RenderCopy(this->getRenderer(), imgTxture, NULL, &txtRect);


	TTF_CloseFont(font);
	SDL_DestroyTexture(imgTxture);
	SDL_FreeSurface(imgTxt);
}

void SDLInitializer::clearScreen() {
	SDL_RenderClear(renderer);
}

void SDLInitializer::drawTexture(SDL_Texture* texture, const SDL_Rect* destRect, SDL_Rect* crop) {
	SDL_RenderCopy(renderer, texture, crop,destRect);

}

void SDLInitializer::drawScreen() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLInitializer::getRenderer() {
	return renderer;
}

SDL_Window* SDLInitializer::getWindow()
{
	return window;
}
