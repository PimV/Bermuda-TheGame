#pragma once
#include <iostream>

#include "GameStateManager.h"

class PlayerUpdateTimer
{
public:
	PlayerUpdateTimer();
	~PlayerUpdateTimer(void);

	static PlayerUpdateTimer* Instance() { return &s_PlayerUpdateTimer; };

	void updateGameTime(long _gameTime);
	long getGameTime();

	bool updateHungerTime();
	bool updateThirstTime();

private:
	static PlayerUpdateTimer s_PlayerUpdateTimer;
	long gameTime;
	long lastHungerUpdate, nextHungerUpdate;
	long lastThirstUpdate, nextThirstUpdate;
};
