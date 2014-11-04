#include "PauseState.h"
#include <iostream>

PauseState PauseState::m_PauseState;
PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	this->gsm = gsm;
	setCurWindow(0);
	mainScr = new PauseMainScreen;
}

void PauseState::pause()
{
}

void PauseState::resume()
{
}

void PauseState::handleEvents(SDL_Event mainEvent)
{
	if (curWindow == 0)
	{
		mainScr->handleEvents(mainEvent);
	}
	else if (curWindow == 1)
	{
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
	if (curWindow == 0)
	{
		mainScr->draw();
	}
	else if (curWindow == 1)
	{

	}
}

void PauseState::cleanup()
{
	delete mainScr;
}

PauseState::~PauseState()
{
	cleanup();
}
