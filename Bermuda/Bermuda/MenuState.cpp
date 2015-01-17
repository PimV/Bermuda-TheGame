#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include <iostream>
#include <SDL_ttf.h>

MenuState MenuState::m_MenuState;

MenuState::MenuState()
{
}

//TODO: remove GSM
void MenuState::init(GameStateManager* gsm)
{
	mainScr = new MenuMainScreen;
	creditsScr = new MenuCreditsScreen;
	helpScr = new MenuHelpScreen;
	loadScr = new MenuLoadScreen;
	graveyardScr = new MenuGraveyardScreen;
	setCurWindow(getMenuMainScreen());

	//soundloader
	SoundLoader::Instance()->playMenuMusic();
}

void MenuState::setCurWindow(BaseScreen* curwindow)
{
	curScreen = curwindow;
	curScreen->resetButtons();
}

BaseScreen* MenuState::getMenuMainScreen()
{
	return mainScr;
}

BaseScreen* MenuState::getMenuCreditsScreen()
{
	return creditsScr;
}

BaseScreen* MenuState::getMenuLoadScreen()
{
	return loadScr;
}

BaseScreen* MenuState::getMenuHelpScreen()
{
	return helpScr;
}

BaseScreen* MenuState::getMenuGraveyardScreen()
{
	return graveyardScr;
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
	delete creditsScr;
	delete helpScr;
	delete loadScr;
	delete graveyardScr;
}

MenuState::~MenuState()
{
}
