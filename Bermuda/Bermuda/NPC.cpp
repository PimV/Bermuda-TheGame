#include "NPC.h"
#include "Spawnpoint.h"
#include "MovableEntity.h"

NPC::NPC(int id, int actionRange, int attackRange, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->spawnPoint = spawnPoint;
	this->behaviour = nullptr;

	this->actionRange = actionRange;
	this->attackRange = attackRange;
}

#pragma region Getters
Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}

BaseBehaviour* NPC::getBehaviour()
{
	return this->behaviour;
}

int NPC::getActionRange()
{
	return this->actionRange;
}

int NPC::getAttackRange()
{
	return this->attackRange;
}

#pragma endregion

#pragma region Setters
void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}
#pragma endregion

NPC::~NPC()
{
}
