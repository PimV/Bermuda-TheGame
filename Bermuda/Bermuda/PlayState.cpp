#include "PlayState.h"
#include <iostream>


PlayState::PlayState(void)
{
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
	std::cout << "Bas Sucks" << std::endl;
}

void PlayState::draw( GameStateManager *gsm) {

}

PlayState::~PlayState(void)
{
}
