#include "ParticleContainer.h"
#include <iostream>

ParticleContainer::ParticleContainer() : IEntityContainer()
{
}

void ParticleContainer::initChunks(int chunksY, int chunksX)
{
	container.resize(chunksY);

	for(size_t i = 0; i < container.size(); i++)
	{
		container[i].resize(chunksX);
	}
}

void ParticleContainer::add(DrawableEntity* entity) 
{
	this->container[entity->getChunkY()][entity->getChunkX()].push_back(entity);
}

void ParticleContainer::remove(DrawableEntity* entity)
{
	std::vector<DrawableEntity*>* vec = &this->container[entity->getChunkY()][entity->getChunkX()];
	std::vector<DrawableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

std::vector<DrawableEntity*>* ParticleContainer::getChunk(int y, int x)
{
	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
	{
		return &this->container[y][x];
	}
	return nullptr;
}


ParticleContainer::~ParticleContainer()
{
}
