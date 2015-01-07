#include "NPC.h"
#include "Spawnpoint.h"
#include "MovableEntity.h"

NPC::NPC(int id, int actionRange, int attackRange, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->spawnPoint = spawnPoint;
	this->behaviour = nullptr;
}

Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}

BaseBehaviour* NPC::getBehaviour()
{
	return this->behaviour;
}

void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}

NPC::~NPC()
{
}
