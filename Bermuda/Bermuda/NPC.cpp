#include "NPC.h"
#include "Spawnpoint.h"

NPC::NPC(int id, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint) : Entity(id)
{
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->walkRange = walkRange;
	this->actionRange = actionRange;
	this->spawnPoint = spawnPoint;
}

NPC::~NPC(void)
{
}
