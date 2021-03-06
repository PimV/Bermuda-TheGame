#include "MovableContainer.h"


MovableContainer::MovableContainer()
{
}

void MovableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
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
	size_t sx = x;
	size_t sy = y;

	if(y >= 0 && x >= 0 && sy < this->container.size() &&  sx < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void MovableContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[y].size(); x++) {
			while (!this->container[y][x].empty())
			{
				MovableEntity* entity = this->container[y][x].back();
				this->container[y][x].pop_back();
				delete entity;
				entity = nullptr;
			}
		}
	}
}

MovableContainer::~MovableContainer()
{
	this->cleanup();
}
