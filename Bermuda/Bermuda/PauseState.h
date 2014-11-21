#pragma once
#include "igamestate.h"
#include "PauzeBaseButton.h"
#include "PauseMainScreen.h"
#include "PauseStatusTrackerScreen.h"
#include "BaseScreen.h"

class PauseState :
	public IGameState
{
private:
	//self (needed for instance)
	static PauseState m_PauseState;

	//variables		Screens
	class BaseScreen* curWindow;
	PauseMainScreen* mainScr;
	PauseStatusTrackerScreen* statScr;

public:
	//variables		Screens
	void setCurWindow(BaseScreen* curwindow);
	BaseScreen* getMainPauseScreen();
	BaseScreen* getMainAchievementsScreen();

	//Methodes
	void pause();								//unused
	void resume();								//unused
	void handleEvents(SDL_Event mainEvent);
	void update(double dt);
	void draw();

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

