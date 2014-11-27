#include "ParticleEngine.h"
#include "GameStateManager.h"


ParticleEngine::ParticleEngine(int x, int y, int width, int height, PARTICLETYPES particleType)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->particleType = particleType;
	//this->textPixel = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelGrey.png").c_str());


	surfPixel= SDL_CreateRGBSurface(0, 3, 3, 8, 0x0, 0x0, 0x0, 255);
	this->textPixel = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->surfPixel);

	switch(this->particleType)
	{
	case PARTICLETYPES::RANDOM:
		this->maxParticles = 1000;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 255);
		break;		
	case PARTICLETYPES::SMOKE:		
		this->maxParticles = 100;
		SDL_SetTextureColorMod(this->textPixel,155,155,155);
		SDL_SetTextureAlphaMod(this->textPixel, 100);
		break;		
	case PARTICLETYPES::RAIN:		
		this->maxParticles = 2000;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 155);
		break;		
	case PARTICLETYPES::SNOW:		
		this->maxParticles = 750;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 255);
		break;
	}

	srand(time(NULL));

	for(int i = 0; i < this->maxParticles; i++)
	{
		this->particles.push_back(this->createParticle(particleType));
	}
}

void ParticleEngine::updateParticles(double dt)
{
	for(int i = 0; i < this->maxParticles; i++)
	{
		if(this->particles[i]->getIsDead())
		{
			delete this->particles[i];
			this->particles[i] = this->createParticle(particleType);
		}
		else
		{
			this->particles[i]->move(dt);
		}
	}
}

void ParticleEngine::drawParticles()
{
	for(int i = 0; i < this->maxParticles; i++)
	{
		this->particles[i]->draw();
	}
}

Particle* ParticleEngine::createParticle(PARTICLETYPES particleType)
{
	float pX = this->x + rand() % this->width;
	float pY = this->y + rand() % this->height;
	float pDx;
	float pDy;
	int lifeTime;
	int width;
	int height;

	switch(particleType)
	{
	case PARTICLETYPES::RANDOM:
		pDx = rand() % 11 - 5 + (float)rand()/(float)RAND_MAX;
		pDy = rand() % 11 - 5 + (float)rand()/(float)RAND_MAX;
		lifeTime = 500 + rand() % 500; 
		width = 1;
		height = 1;

		break;
	case PARTICLETYPES::SMOKE:
		pDx = -0.05;
		pDy = -0.3;
		lifeTime = 800 + rand() % 800;
		width = 3;
		height = 3;

		break;
	case PARTICLETYPES::SNOW:
		pDx = -0.05;
		pDy = 6;
		lifeTime = 1000 + rand() % 800;
		width = 3;
		height = 3;

		break;
	case PARTICLETYPES::RAIN:
		pDx = -0.05;
		pDy = 6;
		lifeTime = 2000 + rand() % 800;
		width = 1;
		height = 9 + rand() % 2;

		break;
	}

	return new Particle(pX, pY, pDx, pDy, lifeTime, this->textPixel, width, height);
}

ParticleEngine::~ParticleEngine()
{
	for(int i = 0; i < this->maxParticles; i++)
	{
		delete this->particles[i];
	}

	SDL_FreeSurface(this->surfPixel);
	SDL_DestroyTexture(this->textPixel);
	this->textPixel = nullptr;
}
