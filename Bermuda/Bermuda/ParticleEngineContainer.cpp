//#include "ParticleEngineContainer.h"
//
//
//ParticleEngineContainer::ParticleEngineContainer()
//{
//}
//
//void ParticleEngineContainer::initChunks(int chunksY, int chunksX)
//{
//	container.resize(chunksY);
//
//	for(size_t i = 0; i < container.size(); i++)
//	{
//		container[i].resize(chunksX);
//	}
//}
//
//void ParticleEngineContainer::add(ParticleEngine* engine) 
//{
//	this->container[engine->getChunkY()][engine->getChunkX()].push_back(engine);
//}
//
//void ParticleEngineContainer::remove(ParticleEngine* engine)
//{
//	std::vector<ParticleEngine*>* vec = &this->container[engine->getChunkY()][engine->getChunkX()];
//	std::vector<ParticleEngine*>::iterator it = std::find(vec->begin(), vec->end(), entity);
//
//	if (it != vec->end()) {
//		vec->erase(it);
//	}
//}
//
//std::vector<DrawableEntity*>* ParticleEngineContainer::getChunk(int y, int x)
//{
//	if(y >= 0 && x >= 0 && y < this->container.size() &&  x < this->container[y].size())
//	{
//		return &this->container[y][x];
//	}
//	return nullptr;
//}
//
//
//ParticleEngineContainer::~ParticleEngineContainer()
//{
//}
