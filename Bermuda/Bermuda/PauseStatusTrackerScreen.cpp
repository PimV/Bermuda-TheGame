#include "PauseStatusTrackerScreen.h"
#include "PlayState.h"
#include "Achievement.h"
#include "PauseState.h"
#include <sstream>


PauseStatusTrackerScreen::PauseStatusTrackerScreen()
{
	init();
}

void PauseStatusTrackerScreen::init()
{
	std::vector<Achievement*> achievements = PlayState::Instance()->getPlayer()->getStatusTracker()->getAllAchievements();

	int total = 0;

	SDL_Color white = { 255, 255, 255 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 16);

	for each (Achievement* var in achievements)
	{
		std::string achievementName = var->getName();
		SDL_Surface* achievementNameSurface = TTF_RenderText_Blended(staryDarzy, achievementName.c_str(), white);
		SDL_Texture* achievementNameTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementNameSurface);
		
		total += achievementNameSurface->h;
		nameSurfaces.push_back(achievementNameSurface);
		nameTextures.push_back(achievementNameTexture);

		int achievementCountInt = var->getAmount();
		ostringstream convert;
		convert << achievementCountInt;

		std::string achievementCount = convert.str();
		SDL_Surface* achievementCountSurface = TTF_RenderText_Blended(staryDarzy, achievementCount.c_str(), white);
		SDL_Texture* achievementCountTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementCountSurface);

		countSurfaces.push_back(achievementCountSurface);
		countTextures.push_back(achievementCountTexture);
	}

	int minSur =  ((int)ScreenHeight - total) / 2;
	for (int i = 0; i < nameSurfaces.size(); i++)
	{
		SDL_Rect rectangeName;
		SDL_Rect rectangeCount;

		rectangeName.h = nameSurfaces.at(i)->h;
		rectangeName.w = nameSurfaces.at(i)->w;
		rectangeName.x = (ScreenWidth / 2) - nameSurfaces.at(i)->w;
		rectangeName.y = minSur;

		rectangeCount.h = countSurfaces.at(i)->h;
		rectangeCount.w = countSurfaces.at(i)->w;
		rectangeCount.x = (ScreenWidth / 2) + 10;
		rectangeCount.y = minSur;

		minSur += nameSurfaces.at(i)->h;

		nameRectangles.push_back(rectangeName);
		countRectangles.push_back(rectangeCount);
	}

	TTF_CloseFont(staryDarzy);
}

void PauseStatusTrackerScreen::handleEvents(SDL_Event mainEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	switch (mainEvent.type)
	{
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			PauseState::Instance()->setCurWindow(0);
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	}
}

void PauseStatusTrackerScreen::draw()
{
	for (int i = 0; i < nameTextures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), nameTextures.at(i), NULL, &nameRectangles.at(i));
	}
	for (int i = 0; i < countTextures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), countTextures.at(i), NULL, &countRectangles.at(i));
	}
}

void PauseStatusTrackerScreen::cleanup()
{

}

PauseStatusTrackerScreen::~PauseStatusTrackerScreen()
{
}
