#include "Rabbit.h"

Rabbit::Rabbit(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int moveSpeed, int actionRange, Spawnpoint* spawnPoint) :
	NPC(id, chunkSize, healthPoints, attackPoints, walkRange, actionRange, spawnPoint),
	Entity(id, 1, 1, chunkSize), 
	IMovable(moveSpeed),
	DrawableEntity(id, 1, 1, chunkSize, nullptr),
	CollidableEntity(id, 1, 1, chunkSize)
{
}

Rabbit::~Rabbit()
{
}