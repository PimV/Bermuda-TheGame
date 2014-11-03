#include "GameTimer.h"

GameTimer::GameTimer(void)
{
	this->self = nullptr;
}

GameTimer::~GameTimer(void)
{
	this->gameTime = NULL;
	delete this->self;
}

GameTimer* GameTimer::init()
{
	if (this->self == nullptr)
	{
		this->gameTime = 0;
		return this;
	}
	else
	{
		return this->self;
	}
}

void GameTimer::updateGameTime(long _gameTime)
{
	this->gameTime += _gameTime;
}

long GameTimer::getGameTime()
{
	return this->gameTime;
}