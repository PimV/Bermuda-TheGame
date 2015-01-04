#include "NPC.h"
#include "Spawnpoint.h"
#include "MovableEntity.h"

#include <iostream>

NPC::NPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->actionRange = actionRange;
	this->attackRange = attackRange;
	this->spawnPoint = spawnPoint;

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;
	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;

	this->behaviour = nullptr;
}

NPC::~NPC()
{
}

#pragma region Getters
int NPC::getHealthPoints()
{
	return this->healthPoints;
}

int NPC::getAttackPoints()
{
	return this->attackPoints;
}

int NPC::getActionRange()
{
	return this->actionRange;
}

int NPC::getAttackRange()
{
	return this->attackRange;
}

Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}

//BaseBehaviour* NPC::getBehaviour()
//{
//	return this->behaviour;
//}
#pragma endregion

#pragma region Setters
void NPC::setHealthPoints(int healthPoints)
{
	this->healthPoints = healthPoints;
}

void NPC::setAttackPoints(int attackPoints)
{
	this->attackPoints = attackPoints;
}

void NPC::setActionRange(int actionRange)
{
	this->actionRange = actionRange;
}

void NPC::setAttackRange(int attackRange)
{
	this->attackRange = attackRange;
}

void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}

#pragma endregion
