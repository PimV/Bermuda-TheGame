#pragma once
#include "igamestate.h"
#include "header_loader.h"
#include "Player.h"
class PlayState :
	public IGameState
{
private:
	static PlayState m_PlayState;

	SDL_Surface* bg;
	int alpha;

public:
	

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

private:
	Player* p;
};

