#include "NPC.h"
#include "Spawnpoint.h"
#include <iostream>

NPC::NPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->actionRange = actionRange;
	this->spawnPoint = spawnPoint;

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;
	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

NPC::~NPC(void)
{
}

#pragma region Getters
int NPC::getHeathPoints()
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

Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}
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

void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}
#pragma endregion

