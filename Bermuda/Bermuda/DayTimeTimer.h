#pragma once
#include <iostream>

#include "GameStateManager.h"

class DayTimeTimer
{
public:
	DayTimeTimer();
	~DayTimeTimer(void);

	void updateGameTime(long _gameTime);
	long getGameTime();

	void updateDayTime();

	int getCurrentDayPart();

private:
	long gameTime, lastDayPartUpdate,  nextDayUpdate;
	int dayParts, currentDayPart;
};

