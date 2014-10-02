#pragma once
#include "header_loader.h"
#include "SDLInitializer.h"
#include "ActionContainer.h"
#include <vector>

class IGameState;

class GameStateManager
{
public:
	GameStateManager(void);

	void init(const char* title, int width, int height, int bpp, bool fullscreen);
	void cleanup();

	void changeGameState(IGameState* gameState);
	void pushGameState(IGameState* gameState);
	void popState();

	void update(double delta);
	void handleEvents();
	void draw();

	ActionContainer* getActionContainer();

	bool running();
	void quit();

	SDLInitializer* sdlInitializer;


	~GameStateManager(void);
private: 
	std::vector<IGameState*> states;
	IGameState *currentState;

	ActionContainer* actionContainer;

	bool m_running;
};

