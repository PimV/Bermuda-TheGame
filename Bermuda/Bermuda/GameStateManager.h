#pragma once
#include "IGameState.h"
class GameStateManager
{
public:
	GameStateManager(void);
	void update(double delta);
	void changeGameState(IGameState* gameState);
	void switchGameState(int index);
	~GameStateManager(void);
private: 
	IGameState *currentState;
	IGameState *gameStates[50];
	void init();
	void cleanupGameStates();
};

