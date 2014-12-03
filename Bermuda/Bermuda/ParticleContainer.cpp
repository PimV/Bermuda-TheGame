#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{ }

ParticleContainer::~ParticleContainer(void)
{
	for( ParticleEngine* pe : this->pEngines)
	{
		delete pe;
	}
	this->pEngines.clear();
	this->pEngines.resize(0);
}

void ParticleContainer::update(double dt)
{
	for( ParticleEngine* pe : this->pEngines)
	{
		pe->updateParticles(dt);
	}
}

void ParticleContainer::draw()
{
	for( ParticleEngine* pe : this->pEngines)
	{
		pe->drawParticles();
	}
}

void ParticleContainer::addEffect(ParticleEngine* _pe)
{
	this->pEngines.push_back(_pe);
}

void ParticleContainer::removeEffect(ParticleEngine* _pe)
{
	auto it = std::find(this->pEngines.begin(), this->pEngines.end(), _pe);

	if(it != this->pEngines.end())
	{
		this->pEngines.erase(it);
	}
}
