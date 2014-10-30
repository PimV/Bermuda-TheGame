#include "Rabbit.h"

Rabbit::Rabbit(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int moveSpeed, int actionRange, Spawnpoint* spawnPoint) :
	NPC(id, chunkSize, healthPoints, attackPoints, walkRange, actionRange, spawnPoint),
	Entity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize),
	DrawableEntity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize, nullptr),
	CollidableEntity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize),
	IMovable(moveSpeed)
{
}

Rabbit::~Rabbit()
{

}