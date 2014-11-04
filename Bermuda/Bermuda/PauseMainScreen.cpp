#include "PauseMainScreen.h"
#include "PauzeMenuButton.h"
#include "PauzeResumeButton.h"
#include "PauzeExitButton.h"
#include "PauzeAchievementsButton.h"
#include <iostream>


PauseMainScreen::PauseMainScreen()
{
	init();
}

void PauseMainScreen::init()
{
	PauzeResumeButton* resumeButton = new PauzeResumeButton(GameStateManager::Instance());
	PauzeMenuButton* menuButton = new PauzeMenuButton(GameStateManager::Instance());
	PauzeExitButton* exitButton = new PauzeExitButton(GameStateManager::Instance());
	PauzeAchievementsButton* achievementsButton = new PauzeAchievementsButton(GameStateManager::Instance());

	achievementsButton->placeAbove(menuButton);
	resumeButton->placeAbove(achievementsButton);
	exitButton->placeUnder(menuButton);


	buttons.push_back(achievementsButton);
	buttons.push_back(resumeButton);
	buttons.push_back(menuButton);
	buttons.push_back(exitButton);
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
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons.at(i)->hover(x, y, gsm);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				buttons.at(i)->clicked(x, y, gsm);
			}
		}
		break;
	}
}

void PauseMainScreen::draw()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw(GameStateManager::Instance());
	}
}

void PauseMainScreen::cleanup()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

PauseMainScreen::~PauseMainScreen()
{
}
