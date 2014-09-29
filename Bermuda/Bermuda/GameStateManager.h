#pragma once
class IGameState;

class GameStateManager
{
public:
	GameStateManager(void);
	void update(double delta);
	void changeGameState(IGameState* gameState);
	~GameStateManager(void);
private: 
	IGameState *currentState;
	IGameState *gameStates[50];
	void init();
	void cleanupGameStates();
};

