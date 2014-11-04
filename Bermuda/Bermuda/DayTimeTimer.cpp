#include "DayTimeTimer.h"

DayTimeTimer DayTimeTimer::s_DayTimeTimer;
DayTimeTimer::DayTimeTimer()
{
	this->dayParts = 24;
	this->currentDayPart = 0;
	this->gameTime = 0;
	this->nextDayUpdate = 0;

	//this->lastDayPartUpdate = 57391; // +- 60 seconds
	//this->lastDayPartUpdate = 25686; // +- ? seconds
	//this->lastDayPartUpdate = 12843; // +- ? seconds
	//this->lastDayPartUpdate = 5422; // +- 11 seconds
	//this->lastDayPartUpdate = 2911; // +- 6 seconds
	this->lastDayPartUpdate = 1500; // +- 3.1 seconds
}

DayTimeTimer::~DayTimeTimer(void)
{
	
}

void DayTimeTimer::updateGameTime(long _gameTime)
{
	this->gameTime += _gameTime;
	this->updateDayTime();
}

void DayTimeTimer::updateDayTime()
{
	long elapsedTime = (GameTimer::Instance()->getGameTime() - this->nextDayUpdate);
	if ( this->lastDayPartUpdate < elapsedTime )
	{
		this->nextDayUpdate = GameTimer::Instance()->getGameTime() + this->lastDayPartUpdate;

		if (this->currentDayPart < this->dayParts)
			this->currentDayPart++;
		else
			this->currentDayPart = 0;
	}
}

int DayTimeTimer::getCurrentDayPart()
{
	return this->currentDayPart;
}