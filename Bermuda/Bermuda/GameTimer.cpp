#include "GameTimer.h"

GameTimer GameTimer::s_GameTimer;
GameTimer::GameTimer(void)
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

GameTimer::~GameTimer(void)
{
	this->gameTime = NULL;
}

void GameTimer::updateGameTime(long _gameTime)
{
	this->gameTime += _gameTime;
}

/*
bool GameTimer::checkTimerAction(long* lastUpdate, long* nextUpdate)
{
	long elapsedTime = this->gameTime - *nextUpdate;
	if ( *lastUpdate < elapsedTime ) {
		*nextUpdate = this->gameTime + *lastUpdate;
		return true;
	}
	return false;
}
*/

long GameTimer::getGameTime()
{
	return this->gameTime;
}

void GameTimer::updateDayTime()
{
	long elapsedTime = (this->getGameTime() - this->nextDayUpdate);
	if ( this->lastDayPartUpdate < elapsedTime )
	{
		this->nextDayUpdate = GameTimer::Instance()->getGameTime() + this->lastDayPartUpdate;

		if (this->currentDayPart < this->dayParts)
			this->currentDayPart++;
		else
			this->currentDayPart = 0;
	}
}

int GameTimer::getCurrentDayPart()
{
	return this->currentDayPart;
}