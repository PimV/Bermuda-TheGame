#pragma once
#include <iostream>

#include "GameTimer.h"

class DayTimeManager
{
public:
	DayTimeManager(GameTimer* _gameTimer);
	~DayTimeManager(void);

	void updateGameTime();
	long getGameTime();

	void updateDayTime();

private:
	GameTimer* gameTimer;
	long gameTime, lastDayPartUpdate,  nextDayUpdate;
	int dayParts, currentDayPart;
};

