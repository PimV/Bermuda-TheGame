#pragma once
#include "igamestate.h"
#include "BasePauzeButton.h"
#include "PauseMainScreen.h"
#include "PauseStatusTrackerScreen.h"
#include "BasePauseScreen.h"

class PauseState :
	public IGameState
{
private:
	static PauseState m_PauseState;
	BasePauseScreen* curWindow = nullptr;

	PauseMainScreen* mainScr;
	PauseStatusTrackerScreen* statScr;

public:
	void setCurWindow(BasePauseScreen*);

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

