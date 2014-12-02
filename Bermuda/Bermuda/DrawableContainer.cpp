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

void DrawableContainer::cleanup() {
	std::cout << "Cleaning Drawable Container" << std::endl;
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
	std::cout << "Drawable Container Cleared - " << itemsDeleted << " items deleted."  << std::endl;
}

DrawableContainer::~DrawableContainer()
{
	this->cleanup();
}
