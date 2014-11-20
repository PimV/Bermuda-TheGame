#pragma once
#include "igamestate.h"
#include "PauzeBaseButton.h"
#include "PauseMainScreen.h"
#include "PauseStatusTrackerScreen.h"
#include "BasePauseScreen.h"

class PauseState :
	public IGameState
{
private:
	//self (needed for instance)
	static PauseState m_PauseState;

	//variables		screens
	class BasePauseScreen* curWindow;

	PauseMainScreen* mainScr;
	PauseStatusTrackerScreen* statScr;

public:
	//Methodes
	void pause();								//unused
	void resume();								//unused
	void handleEvents(SDL_Event mainEvent);
	void update(double dt);
	void draw();
	//			Screens
	void setCurWindow(BasePauseScreen* curwindow);
	BasePauseScreen* getMainPauseScreen();
	BasePauseScreen* getMainAchievementsScreen();

	//getInstance
	static PauseState* Instance() {
		return &m_PauseState;
	};

	//constructors destructors etc
	PauseState();
	void init(GameStateManager* gsm);
	void cleanup();
	virtual ~PauseState();
};

