#include "DrawableContainer.h"
#include <iostream>

DrawableContainer::DrawableContainer() : IEntityContainer()
{
}

void DrawableContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void DrawableContainer::add(DrawableEntity* entity) 
{
	this->container[entity->getChunkY()][entity->getChunkX()].push_back(entity);
}

void DrawableContainer::remove(DrawableEntity* entity)
{
	std::vector<DrawableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<DrawableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<DrawableEntity*>* DrawableContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void DrawableContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[y].size(); x++) {
			while (!this->container[y][x].empty())
			{
				DrawableEntity* entity = this->container[y][x].back();
				this->container[y][x].pop_back();
				delete entity;
			}
		}
	}
}


DrawableContainer::~DrawableContainer()
{
	this->cleanup();
}
