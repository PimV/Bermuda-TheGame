#include "InteractableContainer.h"


InteractableContainer::InteractableContainer()
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

void InteractableContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[y].size(); x++) {
			while (!this->container[y][x].empty())
			{
				InteractableEntity* entity = this->container[y][x].back();
				this->container[y][x].pop_back();
				delete entity;
			}
		}
	}
}

InteractableContainer::~InteractableContainer()
{
	this->cleanup();
}
