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

	float gameTime;
	double frameTime;
	double dayLength;
	double startDay;
	int days;

public:
	GameTimer();
	virtual ~GameTimer();

	static GameTimer* Instance() { return &s_GameTimer; };

	void init();
	void updateGameTime(double frameTime);
	void updateDay();
	float getGameTime();

	double getFullDayLength();
	double getDayLength();
	double getEveningLength();
	double getNightLength();

	double getFrameTime();

	int getDaysSurvived();
	double getPercentage();
	DAYPART getCurrentDayPart();

	void draw();
	void cleanUp();
};
