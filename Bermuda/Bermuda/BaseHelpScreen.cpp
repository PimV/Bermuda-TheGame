#include "BaseHelpScreen.h"

BaseHelpScreen::BaseHelpScreen(int x)
{
	SDL_Surface* s;
	s = SDL_CreateRGBSurface(0, ScreenWidth, ScreenWidth, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 212, 66, 25));
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 71, 60, 51));
	picturePortraitTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);
	//textPortraitTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);
	textPortraitTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "invEditted.bmp").c_str());
	SDL_FreeSurface(s);

	startXPos = x;
	screenWidth = ScreenWidth - x;

	pictureRect.x = startXPos + screenWidth / 8 * 1;
	pictureRect.w = screenWidth / 8 * 6;
	pictureRect.y = ScreenHeight / 12 * 1;
	pictureRect.h = ScreenHeight / 12 * 7;

	textRect.y = ScreenHeight / 12 * 9;
	textRect.x = pictureRect.x;

	textMaxWidth = pictureRect.w;
	textMaxHeight = ScreenHeight / 10 * 2;

	textPortraitRect.x = textRect.x - 2;
	textPortraitRect.w = textMaxWidth + 4;
	textPortraitRect.y = textRect.y - 2;
	textPortraitRect.h = textMaxHeight + 4;

	picturePortraitRect.x = pictureRect.x - 2;
	picturePortraitRect.w = pictureRect.w + 4;
	picturePortraitRect.y = pictureRect.y - 2;
	picturePortraitRect.h = pictureRect.h + 4;
}

void BaseHelpScreen::setPicture(std::string pictureLocation)
{
	pictureTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + pictureLocation).c_str());
}

void BaseHelpScreen::setText(std::string text)
{
	TTF_Font* font = TTF_OpenFont((RESOURCEPATH + "fonts\\andyb.ttf").c_str(), 30);
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), white, textMaxWidth);
	textTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), textSurface);

	textRect.h = textSurface->h;
	textRect.w = textSurface->w;

	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}

void BaseHelpScreen::draw()
{
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	SDL_RenderCopy(renderer, picturePortraitTexture, NULL, &picturePortraitRect);
	SDL_RenderCopy(renderer, textPortraitTexture, NULL, &textPortraitRect);
	SDL_RenderCopy(renderer, pictureTexture, NULL, &pictureRect);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

BaseHelpScreen::~BaseHelpScreen()
{
	SDL_DestroyTexture(pictureTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(picturePortraitTexture);
	SDL_DestroyTexture(textPortraitTexture);
}
