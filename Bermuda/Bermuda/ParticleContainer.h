#pragma once
#include "IEntityContainer.h"
#include "ParticleEngine.h"
#include <vector>

class ParticleContainer : public IEntityContainer
{
private:
	std::vector<ParticleEngine*> pEngines;

public:
	ParticleContainer();
	~ParticleContainer(void);

	void update(double dt);
	void draw();

	void addEffect(ParticleEngine* _pe);
	void removeEffect(ParticleEngine* _pe);
};

