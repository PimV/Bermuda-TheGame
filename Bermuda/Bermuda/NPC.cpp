#include "NPC.h"
#include "Spawnpoint.h"
#include <iostream>

NPC::NPC(int id, Spawnpoint *spawnPoint)  : 
	Entity(id,spawnPoint->getX(),spawnPoint->getY())
{
	this->spawnPoint = spawnPoint;
}

#pragma region Getters
Spawnpoint* NPC::getSpawnPoint()
{
	return this->spawnPoint;
}
#pragma endregion

#pragma region Setters
void NPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}
#pragma endregion

void NPC::interact(Player* player)
{

}

NPC::~NPC()
{
}
