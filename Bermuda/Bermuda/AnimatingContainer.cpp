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
	if (y >= 0 && x >= 0 && y < this->container.size() && x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}

void AnimatingContainer::cleanup()
{
	for (size_t y = 0; y < this->container.size(); y++) {
		for (size_t x = 0; x < this->container[x].size(); x++) {
			while (!this->container[y][x].empty())
			{
				AnimatingEntity* entity = this->container[y][x].back();
				this->container.pop_back();
				delete entity;
			}
		}
	}
}

AnimatingContainer::~AnimatingContainer()
{
	this->cleanup();
}
