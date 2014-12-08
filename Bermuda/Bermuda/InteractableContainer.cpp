#include "InteractableContainer.h"


InteractableContainer::InteractableContainer(void)
{
}

void InteractableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
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
	size_t sx = x;
	size_t sy = y;

	if(y >= 0 && x >= 0 && sy < this->container.size() &&  sx < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

InteractableContainer::~InteractableContainer(void)
{
}
