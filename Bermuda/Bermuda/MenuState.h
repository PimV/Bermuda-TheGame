#pragma once
#include "igamestate.h"
#include "header_loader.h"
class MenuState :
	public IGameState
{
private:
	static MenuState m_MenuState;

	GameStateManager* gsm;

	SDL_Surface* bg;
	int alpha;

public:
	MenuState(void);
	void init(GameStateManager *gsm) ;
	void cleanup();

	void pause();
	void resume();

	void handleEvents() ;
	void update(double dt) ;
	void draw() ;

	static MenuState* Instance() {
		return &m_MenuState;
	}

	~MenuState(void);
};

