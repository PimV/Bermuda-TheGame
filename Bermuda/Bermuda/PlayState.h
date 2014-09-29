#pragma once
#include "igamestate.h"
class PlayState :
	public IGameState
{
public:
	void init();
	void cleanup();

	void pause();
	void resume();

	void handleEvents( GameStateManager *gsm) ;
	void update( GameStateManager *gsm, double dt);
	void draw( GameStateManager *gsm);

	PlayState(void);
	~PlayState(void);
};

