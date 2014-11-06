#include "SpawnpointContainer.h"


SpawnpointContainer::SpawnpointContainer(void)
{
}

void SpawnpointContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(int i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void SpawnpointContainer::add(Spawnpoint* movable) 
{
	this->container[movable->getChunkY()][movable->getChunkX()].push_back(movable);
}

void SpawnpointContainer::remove(Spawnpoint* entity)
{
	std::vector<Spawnpoint*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<Spawnpoint*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<Spawnpoint*>* SpawnpointContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

SpawnpointContainer::~SpawnpointContainer(void)
{
}