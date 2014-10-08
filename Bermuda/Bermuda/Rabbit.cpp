#include "Rabbit.h"

Rabbit::Rabbit(int id, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint) : 
		NPC(id, healthPoints, attackPoints, walkRange, actionRange, spawnPoint)
{
}

Rabbit::~Rabbit()
{
}