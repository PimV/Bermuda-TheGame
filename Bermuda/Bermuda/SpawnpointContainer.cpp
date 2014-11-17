#include "SpawnpointContainer.h"
#include <iostream>

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

void SpawnpointContainer::cleanup() {
	std::cout << "Cleaning Spawnpoint Container" << std::endl;
	int itemsDeleted = 0;
	for (size_t i = 0; i < this->container.size(); i++) {
		for (size_t j = 0; j < this->container[i].size(); j++) {
			for (size_t k = 0; k < this->getChunk(i,j)->size(); k++) {
				itemsDeleted++;
				delete this->getChunk(i,j)->at(k);
			}
			this->getChunk(i,j)->clear();
			this->getChunk(i,j)->shrink_to_fit();
		}
		this->container.shrink_to_fit();

	}
	std::cout << "Spawnpoint Container Cleared - " << itemsDeleted << " items deleted."  << std::endl;
}

SpawnpointContainer::~SpawnpointContainer(void)
{

}
