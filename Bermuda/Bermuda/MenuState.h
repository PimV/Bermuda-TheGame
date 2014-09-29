#pragma once
#include "igamestate.h"
class MenuState :
	public IGameState
{
public:
	MenuState(void);
	void init() ;
	void cleanup();

	void pause();
	void resume();

	void handleEvents( GameStateManager *gsm) ;
	void update( GameStateManager *gsm, double dt) ;
	void draw( GameStateManager *gsm) ;


	~MenuState(void);
};

