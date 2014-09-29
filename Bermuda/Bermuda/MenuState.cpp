#include "MenuState.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include <iostream>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
	counter = 0;
}

void MenuState::init() {

}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}


void MenuState::handleEvents( GameStateManager *gsm) {

}

void MenuState::update( GameStateManager *gsm, double dt) {
	counter++;
	if (counter > 100) {
		counter = 0;
		gsm->changeGameState(PlayState::Instance());
	}
	std::cout << "Pim rocks " << counter <<  std::endl;
}

void MenuState::draw( GameStateManager *gsm) {

}



MenuState::~MenuState(void)
{
}
