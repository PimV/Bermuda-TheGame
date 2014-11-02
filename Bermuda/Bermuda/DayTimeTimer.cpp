#include "DayTimeTimer.h"

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

long DayTimeTimer::getGameTime()
{
	return this->gameTime;
}

void DayTimeTimer::updateGameTime(long _gameTime)
{
	this->gameTime += _gameTime;
	this->updateDayTime();
}

void DayTimeTimer::updateDayTime()
{
	//std::cout << (this->lastDayPartUpdate + this->gameTime) << std::endl;
	if ( this->lastDayPartUpdate < (this->gameTime - this->nextDayUpdate) )
	{
		this->nextDayUpdate = this->gameTime + lastDayPartUpdate;

		if (currentDayPart < dayParts)
			currentDayPart++;
		else
			currentDayPart = 0;
	}
}

int DayTimeTimer::getCurrentDayPart()
{
	return currentDayPart;
}