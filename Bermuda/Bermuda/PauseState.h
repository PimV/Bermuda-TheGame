#pragma once
#include "igamestate.h"

class PauseState :
	public IGameState
{
private:
	GameStateManager* gsm;

public:
	PauseState();

	void init(GameStateManager* gsm);

	void cleanup();
	void pause();
	void resume();

	//TODO: GSM bij deze methodes moet weg...
	void handleEvents(GameStateManager* gsm);
	void update(GameStateManager* gsm, double dt);
	void draw(GameStateManager* gsm);

	void removeState();

	
	virtual ~PauseState();
};

