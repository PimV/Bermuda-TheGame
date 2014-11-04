#pragma once
#include "igamestate.h"
#include "BasePauzeButton.h"
#include "PauseMainScreen.h"

class PauseState :
	public IGameState
{
private:
	GameStateManager* gsm;
	static PauseState m_PauseState;
	int curWindow;
	PauseMainScreen* mainScr;

public:
	void setCurWindow(int);

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent);
	void update(double dt);
	void draw();

	static PauseState* Instance() {
		return &m_PauseState;
	};

	//constructors destructors
	PauseState();
	void init(GameStateManager* gsm);
	void cleanup();
	virtual ~PauseState();
};

