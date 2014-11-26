#include "GameTimer.h"

GameTimer GameTimer::s_GameTimer;

GameTimer::GameTimer(void)
{
}

void GameTimer::init()
{
	this->dayLength = 30000;
	this->gameTime = 0;
	this->startDay = 0;
	this->days = 0;
	this->currentDayPart = DAYPART::Day;
}

void GameTimer::updateGameTime(long gameTime)
{
	this->gameTime += gameTime;
	this->updateDay();
}

long GameTimer::getGameTime()
{
	return this->gameTime;
}

void GameTimer::updateDay()
{
	double percentage = this->getPercentage();

	//If 90% -> night
	if(percentage >= 90 && percentage < 100 && this->currentDayPart != DAYPART::Night)
	{
		this->currentDayPart = DAYPART::Night;
	}
	//If 70& -> evening
	else if(percentage >= 70 && percentage < 90 && this->currentDayPart != DAYPART::Evening)
	{
		this->currentDayPart = DAYPART::Evening;
	}
	//If 0% -> day
	else if(percentage < 70 && this->currentDayPart != DAYPART::Day)
	{
		this->currentDayPart = DAYPART::Day;
	}

	//Day passed
	if((this->startDay + this->dayLength) < this->gameTime)
	{
		this->startDay = this->gameTime;
		this->days++;
	}
}

double GameTimer::getPercentage()
{
	return ((this->gameTime - this->startDay) / this->dayLength) * 100;
}

DAYPART GameTimer::getCurrentDayPart()
{
	return this->currentDayPart;
}

int GameTimer::getDaysSurvived()
{
	return this->days;
}

void GameTimer::draw()
{
}


GameTimer::~GameTimer(void)
{
	this->gameTime = NULL;
}