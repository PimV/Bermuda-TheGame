#include "PauseState.h"
#include <iostream>

PauseState PauseState::m_PauseState;
PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	setCurWindow(0);
	mainScr = new PauseMainScreen;
	statScr = new PauseStatusTrackerScreen;
}

void PauseState::pause()
{
}

void PauseState::resume()
{
}

void PauseState::handleEvents(SDL_Event mainEvent)
{
	curWindow->handleEvents(mainEvent);
//	if (curWindow == 0)
//	{
//		mainScr->handleEvents(mainEvent);
//	}
//	else if (curWindow == 1)
//	{
//		statScr->handleEvents(mainEvent);
//	}
}

void PauseState::update(double dt)
{

}


void PauseState::setCurWindow(BasePauseScreen* window)
{
	curWindow = window;
}

void PauseState::draw()
{
	curWindow->draw();
//	if (curWindow == 0)
//	{
//		mainScr->draw();
//	}
//	else if (curWindow == 1)
//	{
//		statScr->draw();
//	}
}

void PauseState::cleanup()
{
	delete mainScr;
	delete statScr;
}

PauseState::~PauseState()
{

}
