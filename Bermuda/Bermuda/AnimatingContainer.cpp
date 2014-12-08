#include "AnimatingContainer.h"


AnimatingContainer::AnimatingContainer()
{
}

void AnimatingContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for (size_t i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void AnimatingContainer::add(AnimatingEntity* entity)
{
	this->container[entity->getChunkY()][entity->getChunkX()].push_back(entity);
}

void AnimatingContainer::remove(AnimatingEntity* entity)
{
	std::vector<AnimatingEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<AnimatingEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<AnimatingEntity*>* AnimatingContainer::getChunk(int y, int x)
{
	size_t sx = x;
	size_t sy = y;

	if (y >= 0 && x >= 0 && sy < this->container.size() && sx < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

AnimatingContainer::~AnimatingContainer()
{
}
