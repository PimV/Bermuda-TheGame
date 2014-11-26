#include "GameTimer.h"
#include "GameStateManager.h"

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

	//Draw part
	if (textFrame == nullptr) {
		textFrame = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HUD\\frame.png").c_str());
		textCircle = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HUD\\circle.png").c_str());
		textArrow = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HUD\\arrow.png").c_str());

		rectFrame.x = 100;
		rectFrame.y = 100;
		rectFrame.w = 120;
		rectFrame.h = 120;

		rectCircle.x = 105;
		rectCircle.y = 105;
		rectCircle.w = 110;
		rectCircle.h = 110;

		rectArrow.x = 157;
		rectArrow.y = 113;
		rectArrow.w = 6;
		rectArrow.h = 48;
	}
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
	GameStateManager::Instance()->sdlInitializer->drawTexture(textCircle, &rectCircle, NULL);
	GameStateManager::Instance()->sdlInitializer->drawTexture(textFrame, &rectFrame, NULL);
	SDL_Point p = { 2, 46 };
	SDL_RenderCopyEx(	GameStateManager::Instance()->sdlInitializer->getRenderer(),
		textArrow,
		NULL,
		&rectArrow,
		3.6 * this->getPercentage(),
		&p,
		SDL_FLIP_NONE);
}


GameTimer::~GameTimer(void)
{
	this->gameTime = NULL;
}