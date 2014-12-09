#include "LightEntity.h"
#include "GameTimer.h"

#include <iostream>

LightEntity::LightEntity(int id, double x, double y) : Entity(id, x, y)
{
	this->shining = true;
	this->radius = 0;
}

LightEntity::~LightEntity()
{
}


void LightEntity::update(double dt)
{
	// psuedo code:
	// if dayPercent >= 90 && dayPercent <= 99
	// if within a lightsource. set player true

	double p = GameTimer::Instance()->getPercentage();
	if (p >= 90 && p <= 99)
	{
		if (this->shining == true)
		{
			std::cout << "+";
			
		}
		else
		{
			std::cout << "-";
		}
	}
}

bool LightEntity::getShining()
{
	return this->shining;
}

void LightEntity::setShining(bool NewItem)
{
	this->shining = NewItem;
}

double LightEntity::getRadius()
{
	return this->radius;
}
void LightEntity::setRadius(double NewItem)
{
	this->radius = NewItem;
}