#pragma once
#include "header_loader.h"
#include "DAYPART.h"
#include <iostream>

class GameTimer
{
private:
	static GameTimer s_GameTimer;

	SDL_Rect rectArrow;
	SDL_Rect rectCircle;
	SDL_Texture* textCircle;
	SDL_Texture* textArrow;

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
	double getPercentage();
	DAYPART getCurrentDayPart();

	void draw();
	void cleanUp();
};
