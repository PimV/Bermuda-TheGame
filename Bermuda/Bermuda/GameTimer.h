#pragma once
#include <iostream>

class GameTimer
{
private:
	static GameTimer s_GameTimer;

	long gameTime;

	double startDay;
	double dayLength;
	double days;

	/*long lastDayPartUpdate, nextDayUpdate;
	int dayParts, currentDayPart;*/

public:
	GameTimer(void);
	~GameTimer(void);

	static GameTimer* Instance() { return &s_GameTimer; };


	void updateGameTime(long _gameTime);
	void updateDay();
	long getGameTime();

	//bool checkTimerAction(long* lastUpdate, long* nextUpdate);

	//void updateDayTime();
	//int getCurrentDayPart();

	void draw();
};
