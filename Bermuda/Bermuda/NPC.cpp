#include "NPC.h"
#include "Spawnpoint.h"
#include "MovableEntity.h"

NPC::NPC(int id, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->spawnPoint = spawnPoint;
	this->behaviour = nullptr;
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
