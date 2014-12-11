#include "PauseStatusTrackerScreen.h"
#include "PlayState.h"
#include "Achievement.h"
#include "PauseState.h"
#include <sstream>
#include <iostream>


PauseStatusTrackerScreen::PauseStatusTrackerScreen()
{
	this->init();
}

void PauseStatusTrackerScreen::init()
{
	std::vector<Achievement*> achievements = PlayState::Instance()->getPlayer()->getStatusTracker()->getAllAchievements();

	totalHeight = 0;
	int offset = 10;
	int maxCountWidth = 0;
	maxWidth = 0;

	SDL_Color black = { 0, 0, 0 };
	SDL_Color white = { 255, 255, 255 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 24);

	//creating
	for(Achievement* var : achievements)
	{
		//Make achievements names
		std::string achievementName = var->getName();
		SDL_Surface* achievementNameSurface = TTF_RenderText_Blended(staryDarzy, achievementName.c_str(), black);
		SDL_Texture* achievementNameTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), achievementNameSurface);
		
		totalHeight += achievementNameSurface->h;
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

		//Free the surfaces because they are not needed anymore after this
		SDL_FreeSurface(achievementNameSurface);
		SDL_FreeSurface(achievementCountSurface);

		//Setting max width for putting it in the middle of the screen
		int thisWidth = rectangeName.w + rectangeCount.w + offset;
		if (maxWidth < thisWidth)
		{
			maxWidth = thisWidth;
		}
		if (maxCountWidth < rectangeCount.w)
		{
			maxCountWidth = rectangeCount.w;
		}

		nameRectangles.push_back(rectangeName);
		countRectangles.push_back(rectangeCount);

	}
	BaseButton* returnButton = new BaseButton();
	returnButton->createButton("Return", 24, 1);
	returnButton->action = &BaseButton::backToPauseMainScreenAction;
	totalHeight += returnButton->getHeight();
	buttons.push_back(returnButton);

	//aligning
	int minSur =  ((int)ScreenHeight - totalHeight) / 2;
	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		nameRectangles.at(i).x = ((ScreenWidth - maxWidth) / 2 - nameRectangles.at(i).w + maxWidth - offset - maxCountWidth);
		nameRectangles.at(i).y = minSur;

		countRectangles.at(i).x = (ScreenWidth - maxWidth ) / 2 + maxWidth - maxCountWidth;
		countRectangles.at(i).y = minSur;

		minSur += nameRectangles.at(i).h;
	}
	for (BaseButton* var : buttons)
	{
		var->placeMidUnder(ScreenWidth / 2, minSur);
		minSur += var->getHeight();
	}

	TTF_CloseFont(staryDarzy);

	//Background
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/menuBackground.png").c_str());
	setBackground();
}

void PauseStatusTrackerScreen::setBackground()
{
	//set x and width
	backgroundRect.x = (ScreenWidth - maxWidth) / 2;
	backgroundRect.w = maxWidth;

	//padding left and right
	int paddingLR = 35;
	backgroundRect.x -= paddingLR;
	backgroundRect.w += paddingLR * 2;

	//set y and height
	backgroundRect.y = (ScreenHeight - totalHeight) /2;
	backgroundRect.h = totalHeight;

	//padding up and down
	int paddingUD = 35;
	backgroundRect.y -= paddingUD;
	backgroundRect.h += paddingUD * 2;
}

void PauseStatusTrackerScreen::resetButtons()
{
	for (BaseButton* var : buttons)
	{
		var->reset();
	}
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
		for (BaseButton* var : buttons)
		{
			var->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (BaseButton* var : buttons)
			{
				if (var->clicked(x, y))
				{
					break;
				}
			}
		}
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
	for (BaseButton* var : buttons)
	{
		var->draw();
	}
}

void PauseStatusTrackerScreen::cleanup()
{
	SDL_DestroyTexture(this->backgroundTexture);
	this->backgroundTexture = nullptr;

	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		SDL_DestroyTexture(nameTextures[i]);
		nameTextures[i] = nullptr;
	}
	std::vector<SDL_Texture*>().swap(nameTextures); //Clear and shrink vector

	for (size_t i = 0; i < countTextures.size(); i++)
	{
		SDL_DestroyTexture(countTextures[i]);
		countTextures[i] = nullptr;
	}
	std::vector<SDL_Texture*>().swap(countTextures); //Clear and shrink vector

	for (BaseButton* var : buttons)
	{
		delete var;
	}
	std::vector<BaseButton*>().swap(buttons); //Clear and shrink vector
}

PauseStatusTrackerScreen::~PauseStatusTrackerScreen()
{
	this->cleanup();
}
