#include "BackgroundContainer.h"


BackgroundContainer::BackgroundContainer()
{
}

void BackgroundContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(int i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void BackgroundContainer::add(DrawableEntity* drawable) 
{
	this->container[drawable->getChunkY()][drawable->getChunkX()].push_back(drawable);
}

void BackgroundContainer::remove(DrawableEntity* entity)
{
	std::vector<DrawableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<DrawableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<DrawableEntity*>* BackgroundContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

BackgroundContainer::~BackgroundContainer()
{
}
