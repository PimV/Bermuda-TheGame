#include "GameStateManager.h"
#include <iostream>

GameStateManager::GameStateManager(void)
{
}

void GameStateManager::update(double deltaTime) {
	std::cout << deltaTime << std::endl;
}

GameStateManager::~GameStateManager(void)
{
}
