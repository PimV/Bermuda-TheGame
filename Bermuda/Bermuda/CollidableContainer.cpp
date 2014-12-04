#include "CollidableContainer.h"

//TODO : remove methode zoals in drawablecontainer
CollidableContainer::CollidableContainer()
{
}

void CollidableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void CollidableContainer::add(CollidableEntity* collidable) 
{
	this->container[collidable->getChunkY()][collidable->getChunkX()].push_back(collidable);
}

void CollidableContainer::remove(CollidableEntity* entity)
{
	std::vector<CollidableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<CollidableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<CollidableEntity*>* CollidableContainer::getChunk(int y, int x)
{
	size_t sx = x;
	size_t sy = y;

	if(y >= 0 && x >= 0 && sy < this->container.size() &&  sx < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

CollidableContainer::~CollidableContainer(void)
{
}
