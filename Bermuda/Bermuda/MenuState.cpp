#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include "PARTICLETYPES.h"
#include <iostream>
#include <SDL_ttf.h>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
}

//TODO: remove GSM
void MenuState::init(GameStateManager* gsm)
{
	//pEngine = new ParticleEngine(ScreenWidth / 2, ScreenHeight / 2, PARTICLETYPES::SMOKE);
	pEngine = new ParticleEngine(0,0, PARTICLETYPES::SNOW);
	mainScr = new MenuMainScreen;
	creditsScr = new MenuCreditsScreen;
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

void MenuState::handleEvents(SDL_Event mainEvent)
{
	curScreen->handleEvents(mainEvent);
}

void MenuState::draw()
{
	curScreen->draw();
	this->pEngine->drawParticles();
}

void MenuState::update(double dt)
{
	this->pEngine->updateParticles(dt);
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
}

MenuState::~MenuState()
{
}
