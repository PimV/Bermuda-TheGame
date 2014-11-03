#pragma once
#include <iostream>

#include "GameStateManager.h"

class PlayerUpdateTimer
{
public:
	PlayerUpdateTimer();
	~PlayerUpdateTimer(void);

	void updateGameTime(long _gameTime);
	long getGameTime();

	bool updateHungerTime();
	bool updateThirstTime();

private:
	long gameTime;
	long lastHungerUpdate, nextHungerUpdate;
	long lastThirstUpdate, nextThirstUpdate;
};
