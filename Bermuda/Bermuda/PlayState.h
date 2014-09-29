#pragma once
#include "igamestate.h"
class PlayState :
	public IGameState
{
private:
	static PlayState m_PlayState;

public:
	int counter;

	void init();
	void cleanup();

	void pause();
	void resume();

	void handleEvents( GameStateManager *gsm) ;
	void update( GameStateManager *gsm, double dt);
	void draw( GameStateManager *gsm);

	static PlayState* Instance() {
		return &m_PlayState;
	}

	PlayState(void);
	~PlayState(void);
};

