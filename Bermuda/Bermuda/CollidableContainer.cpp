#include "CollidableContainer.h"

//TODO : remove methode zoals in drawablecontainer
CollidableContainer::CollidableContainer()
{
}

std::vector<std::vector<std::vector<CollidableEntity*>>>* CollidableContainer::getContainer()
{
	return &this->container;
}

void CollidableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(int i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void CollidableContainer::add(CollidableEntity* collidable) 
{
	this->container[collidable->getChunkY()][collidable->getChunkX()].push_back(collidable);
}

std::vector<CollidableEntity*>* CollidableContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

CollidableContainer::~CollidableContainer(void)
{
}
