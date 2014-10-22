#include "Rabbit.h"

Rabbit::Rabbit(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint* spawnPoint) : 
	NPC(id, chunkSize, healthPoints, attackPoints, walkRange, actionRange, spawnPoint)
{
}

Rabbit::~Rabbit()
{
}