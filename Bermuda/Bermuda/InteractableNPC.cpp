#include "InteractableNPC.h"
#include <iostream>

InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint):
NPC(id, spawnPoint),
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 0, 0, 0, 0 )
{
	this->animationType = AnimationEnumType::Attackable;
}

#pragma region Getters
int InteractableNPC::getHeathPoints()
{
	return this->healthPoints;
}

int InteractableNPC::getAttackPoints()
{
	return this->attackPoints;
}

int InteractableNPC::getActionRange()
{
	return this->actionRange;
}

Spawnpoint* InteractableNPC::getSpawnPoint()
{
	return this->spawnPoint;
}
#pragma endregion

#pragma region Setters
void InteractableNPC::setHealthPoints(int healthPoints)
{
	this->healthPoints = healthPoints;
}

void InteractableNPC::setAttackPoints(int attackPoints)
{
	this->attackPoints = attackPoints;
}

void InteractableNPC::setActionRange(int actionRange)
{
	this->actionRange = actionRange;
}

void InteractableNPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}
#pragma endregion

void InteractableNPC::interact(Player* player)
{

}

InteractableNPC::~InteractableNPC(void)
{
}
