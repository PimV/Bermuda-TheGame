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

	for(Achievement* var : achievements)
	{
		//Make achievements names
		std::string achievementName = var->getName();
		SDL_Surface* achievementNameSurface = TTF_RenderText_Blended(staryDarzy, achievementName.c_str(), black);
		SDL_Texture* achievementNameTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementNameSurface);
		
		total += achievementNameSurface->h;
		nameTextures.push_back(achievementNameTexture);

		int achievementCountInt = var->getAmount();
		ostringstream convert;
		convert << achievementCountInt;

		//Make achievements number/count
		std::string achievementCount = convert.str();
		SDL_Surface* achievementCountSurface = TTF_RenderText_Blended(staryDarzy, achievementCount.c_str(), black);
		SDL_Texture* achievementCountTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementCountSurface);

		countTextures.push_back(achievementCountTexture);

		//Setting the rectangle heights and widths
		SDL_Rect rectangeName;
		SDL_Rect rectangeCount;

		rectangeName.h = achievementNameSurface->h;
		rectangeName.w = achievementNameSurface->w;

		rectangeCount.h = achievementCountSurface->h;
		rectangeCount.w = achievementCountSurface->w;

		nameRectangles.push_back(rectangeName);
		countRectangles.push_back(rectangeCount);

		//Free the surfaces
		SDL_FreeSurface(achievementNameSurface);
		SDL_FreeSurface(achievementCountSurface);
	}

	int minSur =  ((int)ScreenHeight - total) / 2;
	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		nameRectangles.at(i).x = (ScreenWidth / 2) - nameRectangles.at(i).w - countRectangles.at(i).w ;
		nameRectangles.at(i).y = minSur;

		countRectangles.at(i).x = (ScreenWidth / 2) + 10;
		countRectangles.at(i).y = minSur;

		//placing it somewhat in the middle
		nameRectangles.at(i).x += 100;
		countRectangles.at(i).x += 100;

		minSur += nameRectangles.at(i).h;
	}

	TTF_CloseFont(staryDarzy);

	//Background
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/menuBackground.png").c_str());
	setBackground();
}

void PauseStatusTrackerScreen::setBackground()
{
	backgroundRect.x = ScreenWidth;
	for(SDL_Rect var : nameRectangles)
	{
		if (var.x <= backgroundRect.x)
		{
			backgroundRect.x = var.x;
		}
	}
	//Move background left
	backgroundRect.x = backgroundRect.x - 35;

	backgroundRect.y = ScreenHeight;
	for(SDL_Rect var : nameRectangles)
	{
		if (var.y <= backgroundRect.y)
		{
			backgroundRect.y = var.y;
		}
	}
	//Move background up
	backgroundRect.y = backgroundRect.y - 30;

	backgroundRect.w = 0;
	backgroundRect.h = 0;
	for(SDL_Rect var : nameRectangles)
	{
		backgroundRect.h += var.h;
	}
	//Make background higher
	backgroundRect.h += 60;

	for (size_t i = 0; i < nameRectangles.size(); i++)
	{
		if (nameRectangles.at(i).w + countRectangles.at(i).w >= backgroundRect.w)
		{
			backgroundRect.w = nameRectangles.at(i).w + countRectangles.at(i).w;
		}
	}
	//Make background wider
	backgroundRect.w += 100;
}

void PauseStatusTrackerScreen::resetButtons()
{

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
			PauseState::Instance()->setCurWindow(PauseState::Instance()->getMainPauseScreen());
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
	
	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), nameTextures.at(i), NULL, &nameRectangles.at(i));
	}
	for (size_t i = 0; i < countTextures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), countTextures.at(i), NULL, &countRectangles.at(i));
	}
}

void PauseStatusTrackerScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		SDL_DestroyTexture(nameTextures.at(i));
	}
	nameTextures.clear();
	for (size_t i = 0; i < countTextures.size(); i++)
	{
		SDL_DestroyTexture(countTextures.at(i));
	}
	countTextures.clear();
}

PauseStatusTrackerScreen::~PauseStatusTrackerScreen()
{
	cleanup();
}
