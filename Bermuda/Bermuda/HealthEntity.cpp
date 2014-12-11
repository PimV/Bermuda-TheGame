#include "HealthEntity.h"


HealthEntity::HealthEntity(int id, double x, double y, double maxHealth) :
	Entity(id,x,y)
{
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;
	this->showBar = false;
	timeStartShowBar = 0;
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
}
