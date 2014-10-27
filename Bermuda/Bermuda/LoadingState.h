#pragma once
#include "igamestate.h"
#include "PlayState.h"
#include "header_loader.h"


class LoadingState :
	public IGameState
{
private:
	int i;
	static LoadingState m_LoadingState;
	
	PlayState* playState;
	GameStateManager* gsm;

public:
	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt);
	void draw();

	void setPlayState(PlayState* playState);

	static LoadingState* Instance() {
		return &m_LoadingState;
	};

	LoadingState();
	virtual ~LoadingState();
};

