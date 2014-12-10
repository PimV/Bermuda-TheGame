#include "LightEntity.h"
#include "GameTimer.h"

#include <iostream>

LightEntity::LightEntity(int id, double x, double y) : Entity(id, x, y)
{
	this->shining = true;
	this->diameter = 0;
}

LightEntity::~LightEntity()
{
}

bool LightEntity::getShining()
{
	return this->shining;
}

void LightEntity::setShining(bool NewItem)
{
	this->shining = NewItem;
}

double LightEntity::getDiameter()
{
	return this->diameter;
}
void LightEntity::setDiameter(double NewItem)
{
	this->diameter = NewItem;
}