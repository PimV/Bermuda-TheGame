#include "GameTimer.h"

GameTimer GameTimer::s_GameTimer;

GameTimer::GameTimer(void)
{
}

void GameTimer::init()
{
	this->dayLength = 300000;
	this->gameTime = 0;
	this->startDay = 0;
	this->days = 0;
	this->currentDayPart = DAYPART::Day;
}

void GameTimer::updateGameTime(long gameTime)
{
	std::cout << "New: " << gameTime;
	std::cout << "Cur: " << this->gameTime << std::endl;
	this->gameTime += gameTime;
	this->updateDay();
}

long GameTimer::getGameTime()
{
	return this->gameTime;
}

void GameTimer::updateDay()
{
	//TODO PERCENTAGE IN VAR

	//If 90% -> night
	if(this->getPercentageDay() > 90)
	{
		this->currentDayPart = DAYPART::Night;
	}
	//If 70& -> evening
	else if(this->getPercentageDay() > 70)
	{
		this->currentDayPart = DAYPART::Evening;
	}
	//If 0% -> day
	else if(this->getPercentageDay() < 70 && this->currentDayPart != DAYPART::Day)
	{
		this->currentDayPart = DAYPART::Day;
	}
	//std::cout << this->getPercentageDay() << std::endl;
	//Day passed
	if((this->startDay + this->dayLength) < this->gameTime)
	{
		this->startDay = this->gameTime;
		this->days++;
		//std::cout << "days: " << this->days << std::endl;
	}
}

double GameTimer::getPercentageDay()
{
	//double diff = this->gameTime - this->startDay;
	//double div = diff / this->dayLength;
	//double per = div * 100;
	double percentage = ((this->gameTime - this->startDay) / this->dayLength) * 100;
	return percentage;
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