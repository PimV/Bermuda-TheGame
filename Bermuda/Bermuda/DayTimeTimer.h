#pragma once
#include <iostream>

#include "GameTimer.h"

class DayTimeTimer
{
public:
	DayTimeTimer();
	virtual ~DayTimeTimer(void);

	static DayTimeTimer* Instance() { return &s_DayTimeTimer; };

	void updateGameTime(long _gameTime);

	void updateDayTime();

	int getCurrentDayPart();

private:
	static DayTimeTimer s_DayTimeTimer;
	long gameTime, lastDayPartUpdate,  nextDayUpdate;
	int dayParts, currentDayPart;
};

