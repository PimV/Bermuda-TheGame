#include "SDLInitializer.h"
#include <iostream>

SDLInitializer::SDLInitializer()
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

	// Set icon
	SDL_Surface *surfice = IMG_Load( (RESOURCEPATH + "WindowIco.png").c_str() );
	SDL_SetWindowIcon(window, surfice);
	SDL_FreeSurface(surfice);

	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//Initialize SDL2_ttf
	TTF_Init();

	//TODO: Willen we dit wel gebruiken? Beetje buggy. Veel last van screen tearing en seems.
	//SDL_RenderSetLogicalSize(renderer, 1600, 900);
}

void SDLInitializer::drawText(std::string msg, int x, int y, int w, int h, int fontSize, int r, int g, int b) {
	//TODO: Deze methode is slecht om te gebruiken. Elke frame een nieuwe texture aanmaken kost veel tijd!
	if (fontSize == -1) {
		fontSize = h;
	}

	font = TTF_OpenFont((RESOURCEPATH + "fonts\\segoeuib.ttf").c_str(), fontSize);

	SDL_Surface* imgTxt;
	SDL_Rect txtRect;
	SDL_Color fColor;

	txtRect.x = x;
	txtRect.y = y;
	txtRect.w = msg.length() * h / 3;
	txtRect.h = h;
	
	fColor.r = r;
	fColor.g = g;
	fColor.b = b;
	imgTxt = TTF_RenderText_Blended(font, msg.c_str(), fColor);

	SDL_Texture* imgTxture = SDL_CreateTextureFromSurface(this->getRenderer(), imgTxt);

	SDL_RenderCopy(this->getRenderer(), imgTxture, NULL, &txtRect);


	TTF_CloseFont(font);
	SDL_DestroyTexture(imgTxture);
	SDL_FreeSurface(imgTxt);
}

void SDLInitializer::setRenderDrawColor(int r, int g, int b) {
	SDL_SetRenderDrawColor(this->getRenderer(), r,g,b,255);
}

void SDLInitializer::resetRenderDrawColor() {
	SDL_SetRenderDrawColor(this->getRenderer(), 0,0,0,255);
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

SDLInitializer::~SDLInitializer()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}