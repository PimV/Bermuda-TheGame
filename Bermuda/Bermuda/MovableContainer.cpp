#include "MovableContainer.h"
#include <iostream>

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

void MovableContainer::cleanup() {
	std::cout << "Cleaning Movable Container" << std::endl;
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
	}

	


	std::cout << "Movable Container Cleared - " << itemsDeleted << " items deleted."  << std::endl;
}

MovableContainer::~MovableContainer(void)
{

}
