#include "HealthEntity.h"
#include "GameStateManager.h"


HealthEntity::HealthEntity(int id, double x, double y, double maxHealth) :
	Entity(id,x,y)
{
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;
	this->showBar = false;
	timeStartShowBar = 0;

	greyText = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "health_bar_grey.png").c_str());
	redText = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "health_bar_red.png").c_str());
	
}


double HealthEntity::getHealth()
{
	return this->health;
}

double HealthEntity::getMaxHealth()
{
	return this->maxHealth;
}

void HealthEntity::decreaseHealth(double health)
{
	this->health = this->health - health;

	if(this->health < 0)
	{
		this->health = 0;
	}
}

void HealthEntity::increaseHealth(double health)
{
	this->health = this->health + health;

	if(this->health > this->maxHealth)
	{
		this->health = this->maxHealth;
	}
}

bool HealthEntity::getShowBar()
{
	return this->showBar;
}

void HealthEntity::setShowBar(bool show)
{
	this->showBar = show;
}

double HealthEntity::getPercentageOfCurrentHealth()
{
	return (this->health / this->maxHealth) * 100;
}


void HealthEntity::setTimeStartShowBar(float time)
{
	this->timeStartShowBar = time;
}

float HealthEntity::getTimeStartShowBar()
{
	return this->timeStartShowBar;
}

HealthEntity::~HealthEntity(void)
{
	SDL_DestroyTexture(redText);
	SDL_DestroyTexture(greyText);
	this->redText = nullptr;
	this->greyText = nullptr;
}
