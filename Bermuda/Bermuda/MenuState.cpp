#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include <iostream>
#include <SDL_ttf.h>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
}

//TODO: remove GSM
void MenuState::init(GameStateManager* gsm)
{
	mainScr = new MenuMainScreen;
	creditsScr = new MenuCreditsScreen;
	setCurWindow(getMenuMainScreen());

	//soundloader
	SoundLoader::Instance()->playMenuMusic();

}

void MenuState::setCurWindow(BaseScreen* curwindow)
{
	curScreen = curwindow;
}

BaseScreen* MenuState::getMenuMainScreen()
{
	return mainScr;
}

BaseScreen* MenuState::getMenuCreditsScreen()
{
	return creditsScr;
}

void MenuState::handleEvents(SDL_Event mainEvent)
{
	curScreen->handleEvents(mainEvent);
}

void MenuState::draw()
{
	curScreen->draw();
}

void MenuState::update(double dt)
{
	
}

void MenuState::pause()
{

}

void MenuState::resume()
{

}

void MenuState::cleanup()
{
	delete mainScr;
}

MenuState::~MenuState()
{
	cleanup();
}
