#pragma once
#include <vector>

class IGameState;

class GameStateManager
{
public:
	GameStateManager(void);

	void init();
	void cleanup();

	void changeGameState(IGameState* gameState);
	void pushGameState(IGameState* gameState);
	void popState();

	void update(double delta);
	void handleEvents();
	void draw();

	bool running();
	void quit();


	~GameStateManager(void);
private: 
	std::vector<IGameState*> states;

	IGameState *currentState;
	bool m_running;


};

