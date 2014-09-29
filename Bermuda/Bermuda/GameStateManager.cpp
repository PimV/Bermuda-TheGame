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
	this->currentState->update(this, deltaTime);

}

void GameStateManager::changeGameState(IGameState* gameState) {
	this->currentState = gameState;
}

void GameStateManager::switchGameState(int index) {

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
