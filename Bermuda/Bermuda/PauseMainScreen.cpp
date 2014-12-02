#include "PauseMainScreen.h"
#include "PauseState.h"
#include "MenuState.h"
#include <iostream>
#ifndef BUTTONACTIONS
#define BUTTONACTIONS
#include "ButtonActions.h"
#endif

PauseMainScreen::PauseMainScreen()
{
	init();
}

void PauseMainScreen::init()
{
	//Buttons
	BaseButton* resumeButton = new BaseButton();
	resumeButton->action = resumeGameAction;
	resumeButton->createButton("Resume", 24, 1);

	BaseButton* menuButton = new BaseButton();
	menuButton->action = backToMenuAction;
	menuButton->createButton("Save and back to menu", 24, 1);

	BaseButton* exitButton = new BaseButton();
	exitButton->action = exitAction;
	exitButton->createButton("Save and exit", 24, 1);

	BaseButton* achievementsButton = new BaseButton();
	achievementsButton->action = pauseSetAchievementScreenAction;
	achievementsButton->createButton("Achievements", 24, 1);

	//place buttons
	menuButton->placeMid();
	achievementsButton->placeMidScreenAbove(menuButton);
	resumeButton->placeMidScreenAbove(achievementsButton);
	exitButton->placeMidScreenUnder(menuButton);

	buttons.push_back(achievementsButton);
	buttons.push_back(resumeButton);
	buttons.push_back(menuButton);
	buttons.push_back(exitButton);

	//Background
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/menuBackground.png").c_str());
	setBackground();
}

void PauseMainScreen::setBackground()
{
	backgroundRect.x = ScreenWidth;
	for each (BaseButton* var in buttons)
	{
		if (var->getX() <= backgroundRect.x)
		{
			backgroundRect.x = var->getX();
		}
	}
	//Move backgound left
	backgroundRect.x = backgroundRect.x - 30;

	backgroundRect.y = ScreenHeight;
	for each (BaseButton* var in buttons)
	{
		if (var->getY() <= backgroundRect.y)
		{
			backgroundRect.y = var->getY(); 
		}
	}
	//Move background up
	backgroundRect.y = backgroundRect.y - 30;

	backgroundRect.w = 0;
	backgroundRect.h = 0;

	for each (BaseButton* var in buttons)
	{
		if (var->getWidth() >= backgroundRect.w)
		{
			backgroundRect.w = var->getWidth();
		}
	}
	//Make background wider
	backgroundRect.w += 60;

	for each (BaseButton* var in buttons)
	{
		backgroundRect.h += var->getHeight() * 2;
	}
	//Make background higher
	backgroundRect.h += 0;
}

void PauseMainScreen::resetButtons()
{
	for each (BaseButton* var in buttons)
	{
		var->reset();
	}
}

void PauseMainScreen::handleEvents(SDL_Event mainEvent)
{
	GameStateManager* gsm = GameStateManager::Instance();

	int x, y;
	SDL_GetMouseState(&x, &y);

	switch (mainEvent.type)
	{
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			GameStateManager::Instance()->popState();
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		for (size_t i = 0; i < buttons.size(); i++)
		{
			buttons.at(i)->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (size_t i = 0; i < buttons.size(); i++)
			{
				if (buttons.at(i)->clicked(x, y))
				{
					break;
				}
			}
		}
		break;
	}
}

void PauseMainScreen::draw()
{
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw();
	}
}

void PauseMainScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

PauseMainScreen::~PauseMainScreen()
{
	cleanup();
}
