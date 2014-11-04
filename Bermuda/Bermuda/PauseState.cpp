#include "PauseState.h"

PauseState PauseState::m_PauseState;
PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	this->gsm = gsm;
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
	if (curWindow == 0)
	{
		mainScr->handleEvents(mainEvent);
	}
	else if (curWindow == 1)
	{
		statScr->handleEvents(mainEvent);
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
		statScr->draw();
	}
}

void PauseState::cleanup()
{
	delete mainScr;
	delete statScr;
}

PauseState::~PauseState()
{
	cleanup();
}
