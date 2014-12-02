#include "CollidableContainer.h"
#include <iostream>

//TODO : remove methode zoals in drawablecontainer
CollidableContainer::CollidableContainer()
{
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
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void CollidableContainer::cleanup() {
	std::cout << "Cleaning Collidable Container" << std::endl;
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
	std::cout << "Collidable Container Cleared - " << itemsDeleted << " items deleted."  << std::endl;
}


CollidableContainer::~CollidableContainer(void)
{
	this->cleanup();
}
