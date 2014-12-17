#include "NPC.h"
#include "Spawnpoint.h"
#include <iostream>

NPC::NPC(int id, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->spawnPoint = spawnPoint;
}

Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}

void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}

NPC::~NPC()
{
}
