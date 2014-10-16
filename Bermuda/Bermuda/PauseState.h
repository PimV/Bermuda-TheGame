#pragma once
#include "igamestate.h"

class PauseState :
	public IGameState
{
private:
	GameStateManager* gsm;
	static PauseState m_PauseState;

public:
	PauseState();

	void init(GameStateManager* gsm);

	void cleanup();
	void pause();
	void resume();

	//TODO: GSM bij deze methodes moet weg...
	void handleEvents();
	void update(double dt);
	void draw();

	void removeState();

	static PauseState* Instance() {
		return &m_PauseState;
	};

	virtual ~PauseState();
};

