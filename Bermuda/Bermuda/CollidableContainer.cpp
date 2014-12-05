#include "CollidableContainer.h"

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

void CollidableContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[y].size(); x++) {
			while (!this->container[y][x].empty())
			{
				CollidableEntity* entity = this->container[y][x].back();
				this->container[y][x].pop_back();
				delete entity;
			}
		}
	}
}

CollidableContainer::~CollidableContainer()
{
	this->cleanup();
}
