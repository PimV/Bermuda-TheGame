#include "BaseHelpScreen.h"

BaseHelpScreen::BaseHelpScreen(int x)
{
	SDL_Surface* s;
	s = SDL_CreateRGBSurface(0, ScreenWidth, ScreenWidth, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 251, 0));
	pictureTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);

	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 99, 232, 72));
	textTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);
	SDL_FreeSurface(s);

	startXPos = x;
	screenWidth = ScreenWidth - x;
	pictureRect.x = startXPos + screenWidth / 8 * 1;
	pictureRect.w = screenWidth / 8 * 6;
	textRect.x = pictureRect.x;
	textRect.w = pictureRect.w;

	pictureRect.y = ScreenHeight / 12 * 1;
	pictureRect.h = ScreenHeight / 12 * 7;

	textRect.y = ScreenHeight / 12 * 9;
	textRect.h = ScreenHeight / 12 * 2;
}

void BaseHelpScreen::draw()
{
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	SDL_RenderCopy(renderer, pictureTexture, NULL, &pictureRect);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

BaseHelpScreen::~BaseHelpScreen()
{
	SDL_DestroyTexture(pictureTexture);
	SDL_DestroyTexture(textTexture);
}
