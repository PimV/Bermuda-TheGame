#pragma once
#include <iostream>

class GameTimer
{
public:
	GameTimer(void);
	~GameTimer(void);

	GameTimer* init();
	void updateGameTime(long _gameTime);
	long getGameTime();

private:
	GameTimer* self;
	long gameTime;
};
