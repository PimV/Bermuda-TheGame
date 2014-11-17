#include "PauseStatusTrackerScreen.h"
#include "PlayState.h"
#include "Achievement.h"
#include "PauseState.h"
#include <sstream>
#include <iostream>


PauseStatusTrackerScreen::PauseStatusTrackerScreen()
{
	init();
}

void PauseStatusTrackerScreen::init()
{
	std::vector<Achievement*> achievements = PlayState::Instance()->getPlayer()->getStatusTracker()->getAllAchievements();

	int total = 0;

	SDL_Color black = { 0, 0, 0 };
	SDL_Color white = { 255, 255, 255 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 24);

	for each (Achievement* var in achievements)
	{
		std::string achievementName = var->getName();
		SDL_Surface* achievementNameSurface = TTF_RenderText_Blended(staryDarzy, achievementName.c_str(), black);
		SDL_Texture* achievementNameTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementNameSurface);
		
		total += achievementNameSurface->h;
		nameSurfaces.push_back(achievementNameSurface);
		nameTextures.push_back(achievementNameTexture);

		int achievementCountInt = var->getAmount();
		ostringstream convert;
		convert << achievementCountInt;

		std::string achievementCount = convert.str();
		SDL_Surface* achievementCountSurface = TTF_RenderText_Blended(staryDarzy, achievementCount.c_str(), black);
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

		SDL_FreeSurface(nameSurfaces.at(i));
		SDL_FreeSurface(countSurfaces.at(i));
	}

	TTF_CloseFont(staryDarzy);

	//Background
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/menuBackground.png").c_str());
	setBackground();
}

void PauseStatusTrackerScreen::setBackground()
{
	backgroundRect.x = ScreenWidth;
	for each (SDL_Rect var in nameRectangles)
	{
		if (var.x <= backgroundRect.x)
		{
			backgroundRect.x = var.x;
		}
	}
	backgroundRect.x = backgroundRect.x - 30;

	backgroundRect.y = ScreenHeight;
	for each (SDL_Rect var in nameRectangles)
	{
		if (var.y <= backgroundRect.y)
		{
			backgroundRect.y = var.y;
		}
	}
	backgroundRect.y = backgroundRect.y - 30;

	backgroundRect.w = 0;
	backgroundRect.h = 0;
	for each (SDL_Rect var in nameRectangles)
	{
		backgroundRect.h += var.h;
	}
	backgroundRect.h += 60;

	for (size_t i = 0; i < nameRectangles.size(); i++)
	{
		if (nameRectangles.at(i).w + countRectangles.at(i).w >= backgroundRect.w)
		{
			backgroundRect.w = nameRectangles.at(i).w + countRectangles.at(i).w;
		}
	}
	backgroundRect.w += 70;
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
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	
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
	for (int i = 0; i < nameTextures.size(); i++)
	{
		SDL_DestroyTexture(nameTextures.at(i));
	}
	nameTextures.clear();
	for (int i = 0; i < countTextures.size(); i++)
	{
		SDL_DestroyTexture(countTextures.at(i));
	}
	countTextures.clear();
}

PauseStatusTrackerScreen::~PauseStatusTrackerScreen()
{
	cleanup();
}
