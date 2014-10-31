#pragma once
#include <iostream>

#include "GameTimer.h"

class PlayerUpdateTimer
{
public:
	PlayerUpdateTimer(GameTimer* _gameTimer);
	~PlayerUpdateTimer(void);

	void updateGameTime();
	long getGameTime();

	void updateDayTime();

private:
	GameTimer* gameTimer;
	long gameTime, lastUpdate,  nextUpdate;
	int dayParts, currentDayPart;
};

