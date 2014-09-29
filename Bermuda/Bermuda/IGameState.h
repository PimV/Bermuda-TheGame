#pragma once
#include "GameStateManager.h"

class IGameState
{
protected:
	IGameState() { }
public:


	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(GameStateManager* gsm) = 0;
	virtual void update(GameStateManager* gsm, double dt) = 0;
	virtual void draw(GameStateManager* gsm) = 0;

	void ChangeState(GameStateManager* gsm, IGameState* state) {
		gsm->changeGameState(state);
	}

	virtual ~IGameState(void);
};

