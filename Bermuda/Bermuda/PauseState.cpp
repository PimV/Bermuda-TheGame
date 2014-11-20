#include "PauseState.h"
#include <iostream>

PauseState PauseState::m_PauseState;
PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	mainScr = new PauseMainScreen;
	statScr = new PauseStatusTrackerScreen;

	setCurWindow(mainScr);
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
}

void PauseState::update(double dt)
{

}

void PauseState::setCurWindow(BasePauseScreen* window)
{
	curWindow = window;
}

BasePauseScreen* PauseState::getMainPauseScreen()
{
	return mainScr;
}

BasePauseScreen* PauseState::getMainAchievementsScreen()
{
	return statScr;
}

void PauseState::draw()
{
	curWindow->draw();
}

void PauseState::cleanup()
{
	delete mainScr;
	delete statScr;
}

PauseState::~PauseState()
{

}
