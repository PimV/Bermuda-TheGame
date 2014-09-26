#pragma once
#include "igamestate.h"
class MenuState :
	public IGameState
{
public:
	void init();
	void update(double dt);
	void draw();
	void handleInput();
	MenuState(void);
	virtual ~MenuState(void);
};

