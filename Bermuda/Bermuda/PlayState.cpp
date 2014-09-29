#include "PlayState.h"
#include "MenuState.h"
#include "GameStateManager.h"
#include <iostream>

PlayState PlayState::m_PlayState;

PlayState::PlayState(void)
{
	counter = 0;
}


void PlayState::init() {

}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {

}


void PlayState::handleEvents( GameStateManager *gsm) {

}

void PlayState::update(GameStateManager *gsm, double dt) {
	counter++;
	if (counter > 100) {
		counter = 0;
		gsm->changeGameState(MenuState::Instance());
	}
	std::cout << "Bas Sucks " << counter <<   std::endl;
}

void PlayState::draw( GameStateManager *gsm) {

}

PlayState::~PlayState(void)
{
}
