#include "GameTimer.h"
#include "GameStateManager.h"

GameTimer GameTimer::s_GameTimer;

GameTimer::GameTimer()
{
}

void GameTimer::init()
{
	this->dayLength = 60000;
	this->gameTime = 0;
	this->frameTime = 0;
	this->startDay = 0;
	this->days = 0;
	this->currentDayPart = DAYPART::Day;

	//Draw part
	
	textCircle = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HUD\\circleTotal.png").c_str());
	textArrow = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HUD\\arrow.png").c_str());

	rectCircle.w = ScreenWidth / 10;
	rectCircle.h = rectCircle.w;
	rectCircle.x = ScreenWidth - rectCircle.w - rectCircle.w / 4;
	rectCircle.y = rectCircle.w / 4;

	rectArrow.w = 6;
	rectArrow.h = rectCircle.h / 2 - rectCircle.h / 10;
	rectArrow.x = rectCircle.x + rectCircle.w / 2 - rectArrow.w / 2;
	rectArrow.y = rectCircle.y + rectCircle.h / 2 - rectArrow.h + 2;

}

void GameTimer::updateGameTime(double frameTime)
{
	this->frameTime = frameTime;
	this->gameTime += static_cast<float>(frameTime);
	this->updateDay();
}

float GameTimer::getGameTime()
{
	return this->gameTime;
}

void GameTimer::setGameTime(double gameTime)
{
	this->gameTime = static_cast<float>(gameTime);
}

double GameTimer::getFullDayLength()
{
	return this->dayLength;
}

double GameTimer::getDayLength()
{
	return this->dayLength / 100 * 70;
}

double GameTimer::getEveningLength()
{
	return this->dayLength / 100 * 20;
}

double GameTimer::getNightLength()
{
	return this->dayLength / 100 * 10;
}

double GameTimer::getFrameTime()
{
	return this->frameTime;
}

void GameTimer::updateDay()
{
	double percentage = this->getPercentage();

	//If 90% -> night
	if(percentage >= 90 && percentage < 100 && this->currentDayPart != DAYPART::Night)
	{
		this->currentDayPart = DAYPART::Night;
	}
	//If 70% -> evening
	else if(percentage >= 70 && percentage < 90 && this->currentDayPart != DAYPART::Evening)
	{
		this->currentDayPart = DAYPART::Evening;
	}
	//If 0% -> day
	else if(percentage < 70 && this->currentDayPart != DAYPART::Day)
	{
		this->currentDayPart = DAYPART::Day;
	}
}

double GameTimer::getPercentage()
{
	return fmod(this->gameTime, this->dayLength) / this->dayLength * 100;
}

DAYPART GameTimer::getCurrentDayPart()
{
	return this->currentDayPart;
}

int GameTimer::getDaysSurvived()
{
	return static_cast<int>(floor(this->gameTime / this->dayLength));
}

void GameTimer::draw()
{
	//Draw circle
	GameStateManager::Instance()->sdlInitializer->drawTexture(textCircle, &rectCircle, NULL);

	SDL_Point rotatePoint = { rectArrow.w / 2, rectArrow.h - 3 };
	//Draw arrow in right direction
	SDL_RenderCopyEx(	GameStateManager::Instance()->sdlInitializer->getRenderer(),
		textArrow,
		NULL,
		&rectArrow,
		3.6 * this->getPercentage(),
		&rotatePoint,
		SDL_FLIP_NONE);

	//Draw amount of days
	GameStateManager::Instance()->sdlInitializer->setRenderDrawColor(255,255,255);
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("Day " + to_string(GameTimer::Instance()->getDaysSurvived())), rectCircle.x + rectCircle.w / 5, rectCircle.y + rectCircle.h / 3, rectCircle.w / 3, rectCircle.h / 4, 0, 0, 0);
	GameStateManager::Instance()->sdlInitializer->resetRenderDrawColor();
}
void GameTimer::cleanUp()
{
	SDL_DestroyTexture(textCircle);
	SDL_DestroyTexture(textArrow);
}

GameTimer::~GameTimer()
{
	this->cleanUp();
}
