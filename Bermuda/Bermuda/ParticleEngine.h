#pragma once
#include "header_loader.h"
#include "Particle.h"
#include "PARTICLETYPES.h"
#include <vector>
#include <ctime>

class ParticleEngine
{
private:
	std::vector<Particle*> particles;
	int x;
	int y;
	int width;
	int height;
	int maxParticles;

	PARTICLETYPES particleType;

	SDL_Surface* surfPixel;
	SDL_Texture* textPixel;

	Particle* createParticle(PARTICLETYPES particleType);

public:
	ParticleEngine(int x, int y, int width, int height, PARTICLETYPES);
	virtual ~ParticleEngine();

	void updateParticles(double dt);
	void drawParticles();
};

