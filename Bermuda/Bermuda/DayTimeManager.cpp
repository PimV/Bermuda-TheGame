#include "DayTimeManager.h"

DayTimeManager::DayTimeManager(GameTimer* _gameTimer)
{
	this->gameTimer = _gameTimer;
	this->dayParts = 10;
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


DayTimeManager::~DayTimeManager(void)
{
	// don't clear the gameTimer
}

void DayTimeManager::updateGameTime()
{
	this->gameTime = gameTimer->getGameTime();
	this->updateDayTime();
}

void DayTimeManager::updateDayTime()
{
	//std::cout << (this->lastDayPartUpdate + this->gameTime) << std::endl;
	if ( this->lastDayPartUpdate < (this->gameTime - this->nextDayUpdate) )
	{
		this->nextDayUpdate = this->gameTime + lastDayPartUpdate;

		if (currentDayPart < 10)
			currentDayPart++;
		else
			currentDayPart = 1;

		std::cout << "Current Daypart: " << currentDayPart << std::endl;
	}
}