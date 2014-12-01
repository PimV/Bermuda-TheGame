#pragma once
#include "header_loader.h"
#include "DrawableEntity.h"
#include "Camera.h"
#include "Particle.h"
#include "PARTICLETYPES.h"
#include <vector>
#include <ctime>

class ParticleEngine :
	public DrawableEntity
{
private:
	std::vector<Particle*> particles;
	int x;
	int y;
	int width;
	int height;
	int maxParticles;
	int currentMaxParticles;

	PARTICLETYPES particleType;

	SDL_Surface* surfPixel;
	SDL_Texture* textPixel;

	Particle* createParticle(PARTICLETYPES particleType);

public:
	ParticleEngine(int id, double x, double y, Image* image, PARTICLETYPES);
	virtual ~ParticleEngine();

	void updateParticles(double dt);
	void draw(Camera* camera, SDL_Renderer* renderer);
};