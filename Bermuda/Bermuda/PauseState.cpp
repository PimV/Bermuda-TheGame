#include "PauseState.h"
#include "PauzeMenuButton.h"
#include "PauzeResumeButton.h"
#include "PauzeExitButton.h"
#include "PauzeAchievementsButton.h"

PauseState PauseState::m_PauseState;

PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	this->gsm = gsm;
	setCurWindow(0);

	PauzeResumeButton* resumeButton = new PauzeResumeButton(gsm);
	PauzeMenuButton* menuButton = new PauzeMenuButton(gsm);
	PauzeExitButton* exitButton = new PauzeExitButton(gsm);
	PauzeAchievementsButton* achievementsButton = new PauzeAchievementsButton(gsm);

	achievementsButton->placeAbove(menuButton);
	resumeButton->placeAbove(achievementsButton);
	exitButton->placeUnder(menuButton);


	buttons.push_back(achievementsButton);
	buttons.push_back(resumeButton);
	buttons.push_back(menuButton);
	buttons.push_back(exitButton);
}

void PauseState::pause()
{
}

void PauseState::resume()
{
}

void PauseState::handleEvents(SDL_Event mainEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch(mainEvent.type) 
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

void PauseState::update(double dt)
{

}


void PauseState::setCurWindow(int window)
{
	curWindow = window;
}

void PauseState::draw()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw(gsm);
	}
}

void PauseState::cleanup()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

PauseState::~PauseState()
{
	cleanup();
}
