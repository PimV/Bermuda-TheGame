#pragma once
#include <iostream>

class GameTimer
{
public:
	GameTimer(void);
	~GameTimer(void);

	static GameTimer* Instance() { return &s_GameTimer; };
	void updateGameTime(long _gameTime);
	long getGameTime();

	bool checkTimerAction(long* lastUpdate, long* nextUpdate);

	void updateDayTime();
	int getCurrentDayPart();

private:
	static GameTimer s_GameTimer;
	long gameTime;
	long lastDayPartUpdate, nextDayUpdate;
	int dayParts, currentDayPart;
};
