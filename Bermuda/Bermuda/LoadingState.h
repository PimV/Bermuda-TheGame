#pragma once
#include "igamestate.h"
#include "header_loader.h"


class LoadingState :
	public IGameState
{
private:
	int i;
	static LoadingState m_LoadingState;
	
	GameStateManager* gsm;

public:
	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt);
	void draw();

	static LoadingState* Instance() {
		return &m_LoadingState;
	};

	LoadingState();
	virtual ~LoadingState();
};

