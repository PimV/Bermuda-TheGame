#include "MenuState.h"
#include <iostream>


MenuState::MenuState(void)
{
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
	std::cout << "Pim rocks" << std::endl;
}

void MenuState::draw( GameStateManager *gsm) {

}



MenuState::~MenuState(void)
{
}
