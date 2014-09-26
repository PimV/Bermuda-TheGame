#pragma once
#include "igamestate.h"
class PlayState :
	public IGameState
{
public:
	void init();
	void update(double dt);
	void draw();
	void handleInput();
	PlayState(void);
	virtual ~PlayState(void);
};

