#include "PlayerUpdateTimer.h"


PlayerUpdateTimer::PlayerUpdateTimer()
{
	this->gameTime = 0;

	this->lastHungerUpdate = 2200, this->nextHungerUpdate = 0;
	this->lastThurstUpdate = 1500; this->nextThurstUpdate = 0;// +- 3.1 seconds
}

PlayerUpdateTimer::~PlayerUpdateTimer(void)
{
}

void PlayerUpdateTimer::updateGameTime(long _gameTime)
{
	this->gameTime += _gameTime;
}

bool PlayerUpdateTimer::updateHungerTime()
{
	if ( this->lastHungerUpdate < (this->gameTime - this->nextHungerUpdate) )
	{
		this->nextHungerUpdate = this->gameTime + this->lastHungerUpdate;
		return true;
	}
	return false;
}

bool PlayerUpdateTimer::updateThurstTime()
{
	if ( this->lastThurstUpdate < (this->gameTime - this->nextThurstUpdate) )
	{
		this->nextThurstUpdate = this->gameTime + this->lastThurstUpdate;
		return true;
	}
	return false;
}