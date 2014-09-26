#include "GameStateManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>

GameStateManager::GameStateManager(void) {
	this->init();
}

void GameStateManager::init() {
	this->gameStates[0] = new MenuState();
	this->gameStates[1] = new PlayState();

	this->currentState = gameStates[1];
}

void GameStateManager::update(double deltaTime) {
	this->currentState->update(deltaTime);

}

void GameStateManager::switchGameState(int index) {
	this->currentState = gameStates[index];
}

GameStateManager::~GameStateManager(void) {
	this->cleanupGameStates();
}


void GameStateManager::cleanupGameStates() {
	for (IGameState *i : this->gameStates) {
		delete i;
	}
	delete [] this->gameStates;
}
