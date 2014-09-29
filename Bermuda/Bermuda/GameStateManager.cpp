#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>


GameStateManager::GameStateManager(void) {
	this->init();
}

void GameStateManager::init() {
	this->currentState = MenuState::Instance();
}

void GameStateManager::update(double deltaTime) {
	this->currentState->update(this, deltaTime);

}

void GameStateManager::changeGameState(IGameState* gameState) {
	this->currentState = gameState;
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
