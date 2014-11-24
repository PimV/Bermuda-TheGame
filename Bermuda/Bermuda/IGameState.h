#pragma once
#include "GameStateManager.h"

class IGameState
{
protected:
	IGameState() { }
public:

	virtual void init(GameStateManager *gsm) = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(SDL_Event mainEvent) = 0;
	virtual void update(double dt) = 0;
	virtual void draw() = 0;

	void ChangeState(GameStateManager* gsm, IGameState* state) {
		gsm->changeGameState(state);
	}

	virtual ~IGameState(void);
};

