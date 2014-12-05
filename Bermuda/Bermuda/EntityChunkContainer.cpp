#include "EntityChunkContainer.h"

EntityChunkContainer::EntityChunkContainer()
{
}

void EntityChunkContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void EntityChunkContainer::add(Entity* entity) 
{
	this->container[entity->getChunkY()][entity->getChunkX()].push_back(entity);
}

void EntityChunkContainer::remove(Entity* entity)
{
	std::vector<Entity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<Entity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<Entity*>* EntityChunkContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void EntityChunkContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[y].size(); x++) {
			while (!this->container[y][x].empty())
			{
				Entity* entity = this->container[y][x].back();
				this->container[y][x].pop_back();
				delete entity;
			}
		}
	}
}

EntityChunkContainer::~EntityChunkContainer()
{
	this->cleanup();
}
