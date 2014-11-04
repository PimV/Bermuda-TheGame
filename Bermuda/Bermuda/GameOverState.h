#pragma once
#include "IGameState.h"
#include <string.h>

class GameOverState : public IGameState
{
private:
	GameStateManager* gsm;
	static GameOverState m_GameOverState;

	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;

	SDL_Texture* gameOverMessageTexture;
	SDL_Rect gameoverMessageRect;

	SDL_Texture* continueMessageTexture;
	SDL_Rect continueMessageRect;

public:
	//Variables

	//Methodes
	void init(GameStateManager* gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent);
	void update(double dt);
	void draw();

	void removeState();

	static GameOverState* Instance() {
		return &m_GameOverState;
	}

	//Constructors and destructors
	GameOverState();
	virtual ~GameOverState();
};

