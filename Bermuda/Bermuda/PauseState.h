#pragma once
#include "igamestate.h"
#include "BasePauzeButton.h"

class PauseState :
	public IGameState
{
private:
	GameStateManager* gsm;
	static PauseState m_PauseState;
	std::string curWindow;
	std::vector<BasePauzeButton*> buttons;

public:
	void setCurWindow();

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

