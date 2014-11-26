#pragma once
#include "DAYPART.h"
#include <iostream>

class GameTimer
{
private:
	static GameTimer s_GameTimer;

	DAYPART currentDayPart;

	long gameTime;
	double dayLength;
	double startDay;
	int days;

public:
	GameTimer(void);
	~GameTimer(void);

	static GameTimer* Instance() { return &s_GameTimer; };

	void init();
	void updateGameTime(long gameTime);
	void updateDay();
	long getGameTime();

	int getDaysSurvived();
	double getPercentageDay();
	DAYPART getCurrentDayPart();

	void draw();
};
