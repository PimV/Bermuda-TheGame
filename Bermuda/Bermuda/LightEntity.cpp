#include "LightEntity.h"


LightEntity::LightEntity(int id, double x, double y) : Entity(id, x, y)
{
	this->shining = true;
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