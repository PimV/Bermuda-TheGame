#include "PlayerUpdateTimer.h"


PlayerUpdateTimer::PlayerUpdateTimer()
{
	this->gameTime = 0;

	this->lastHungerUpdate = 2200, this->nextHungerUpdate = 0;
	this->lastThirstUpdate = 1500; this->nextThirstUpdate = 0;// +- 3.1 seconds
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

bool PlayerUpdateTimer::updateThirstTime()
{
	if ( this->lastThirstUpdate < (this->gameTime - this->nextThirstUpdate) )
	{
		this->nextThirstUpdate = this->gameTime + this->lastThirstUpdate;
		return true;
	}
	return false;
}