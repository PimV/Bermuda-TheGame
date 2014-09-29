#pragma once
#include "header_loader.h"
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

	bool running();
	void quit();

	SDL_Surface* screen;
	SDL_Window* window;
	SDL_Renderer* renderer;

	~GameStateManager(void);
private: 
	std::vector<IGameState*> states;

	IGameState *currentState;
	bool m_running;


};

