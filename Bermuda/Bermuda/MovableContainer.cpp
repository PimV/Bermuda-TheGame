#include "MovableContainer.h"


MovableContainer::MovableContainer(void)
{
}

void MovableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(int i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void MovableContainer::add(MovableEntity* movable) 
{
	this->container[movable->getChunkY()][movable->getChunkX()].push_back(movable);
}

void MovableContainer::remove(MovableEntity* entity)
{
	std::vector<MovableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<MovableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<MovableEntity*>* MovableContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

MovableContainer::~MovableContainer(void)
{
}