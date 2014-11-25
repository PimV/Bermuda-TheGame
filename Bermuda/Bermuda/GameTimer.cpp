#include "GameTimer.h"

GameTimer GameTimer::s_GameTimer;
GameTimer::GameTimer(void)
{
	this->gameTime = 0;
	this->dayLength = 5000;
	this->startDay = 0;
	this->days = 0;
	/*this->dayParts = 24;
	this->currentDayPart = 0;
	this->gameTime = 0;
	this->nextDayUpdate = 0;*/

	//this->lastDayPartUpdate = 57391; // +- 60 seconds
	//this->lastDayPartUpdate = 25686; // +- ? seconds
	//this->lastDayPartUpdate = 12843; // +- ? seconds
	//this->lastDayPartUpdate = 5422; // +- 11 seconds
	//this->lastDayPartUpdate = 2911; // +- 6 seconds
	//this->lastDayPartUpdate = 1500; // +- 3.1 seconds
}

void GameTimer::updateGameTime(long gameTime)
{
	this->gameTime += gameTime;
	this->updateDay();
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

void GameTimer::updateDay()
{
	//Day passed
	if(this->startDay + this->dayLength < this->gameTime)
	{
		this->startDay = this->gameTime;
		this->days++;
		std::cout << "days: " << this->days << std::endl;
		std::cout << "gameTime: " << this->gameTime << std::endl;
	}

	std::cout << "% till next day: " << ((this->gameTime - this->startDay) / this->dayLength) * 100 << std::endl;
}

//void GameTimer::updateDayTime()
//{
//	long elapsedTime = (this->getGameTime() - this->nextDayUpdate);
//	if ( this->lastDayPartUpdate < elapsedTime )
//	{
//		this->nextDayUpdate = GameTimer::Instance()->getGameTime() + this->lastDayPartUpdate;
//
//		if (this->currentDayPart < this->dayParts)
//		{
//			this->currentDayPart++;
//		}
//		else
//		{
//			this->currentDayPart = 0;
//		}
//	}
//}

//int GameTimer::getCurrentDayPart()
//{
//	return this->currentDayPart;
//}

void GameTimer::draw()
{
}


GameTimer::~GameTimer(void)
{
	this->gameTime = NULL;
}