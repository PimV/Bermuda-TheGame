#include "InteractableContainer.h"
#include <iostream>

InteractableContainer::InteractableContainer(void)
{
}

void InteractableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(int i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void InteractableContainer::add(InteractableEntity* entity) 
{
	this->container[entity->getChunkY()][entity->getChunkX()].push_back(entity);
}

void InteractableContainer::remove(InteractableEntity* entity)
{
	std::vector<InteractableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<InteractableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<InteractableEntity*>* InteractableContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void InteractableContainer::cleanup() {
	std::cout << "Cleaning Interactable Container" << std::endl;
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
	std::cout << "Interactable Container Cleared - " << itemsDeleted << " items deleted."  << std::endl;
}

InteractableContainer::~InteractableContainer(void)
{
	this->cleanup();
}
