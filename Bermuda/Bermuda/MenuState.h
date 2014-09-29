#pragma once
#include "igamestate.h"
class MenuState :
	public IGameState
{
private:
	static MenuState m_MenuState;
	int counter;

public:
	MenuState(void);
	void init() ;
	void cleanup();

	void pause();
	void resume();

	void handleEvents( GameStateManager *gsm) ;
	void update( GameStateManager *gsm, double dt) ;
	void draw( GameStateManager *gsm) ;

	static MenuState* Instance() {
		return &m_MenuState;
	}

	~MenuState(void);
};

