#include "ParticleEngine.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include <thread>
#include <iostream>

ParticleEngine::ParticleEngine(int id, double x, double y, Image* image, PARTICLETYPES particleType) : 
	Entity(0, x, y),
	DrawableEntity(0, x, y, nullptr)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

	this->x = x;
	this->y = y;
	this->setHeight(0);
	this->particleType = particleType;
	this->currentMaxParticles = 0;


	surfPixel= SDL_CreateRGBSurface(0, 3, 3, 8, 0x0, 0x0, 0x0, 255);
	this->textPixel = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->surfPixel);

	switch(this->particleType)
	{
	case PARTICLETYPES::RANDOM:
		this->maxParticles = 1000;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 255);
		this->width = 10;
		this->height = 10;
		break;		
	case PARTICLETYPES::SMOKE:		
		this->maxParticles = 150;
		SDL_SetTextureColorMod(this->textPixel,155,155,155);
		SDL_SetTextureAlphaMod(this->textPixel, 100);
		this->width = 25;
		this->height = 5;
		break;		
	case PARTICLETYPES::RAIN:		
		this->maxParticles = 2000;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 155);
		this->width = ScreenWidth;
		this->height = 1;
		break;		
	case PARTICLETYPES::SNOW:		
		this->maxParticles = 750;
		SDL_SetTextureColorMod(this->textPixel,255,255,255);
		SDL_SetTextureAlphaMod(this->textPixel, 255);
		this->width = ScreenWidth;
		this->height = 1;
		break;
	}

	srand(time(NULL));

	for(int i = 0; i < this->maxParticles; i++)
	{
		this->particles.push_back(nullptr);
	}
}

void ParticleEngine::updateParticles(double dt)
{
	for(int i = 0; i < this->currentMaxParticles; i++)
	{
		if(this->particles[i] == nullptr || this->particles[i]->getIsDead())
		{
			delete this->particles[i];
			this->particles[i] = this->createParticle(particleType);
		}
		else
		{
			this->particles[i]->move(dt);
		}
	}

	if(this->currentMaxParticles < this->maxParticles)
	{
		this->currentMaxParticles++;
	}
}

void ParticleEngine::draw(Camera* camera, SDL_Renderer* renderer)
{
	for(int i = 0; i < this->currentMaxParticles; i++)
	{
		if(this->particles[i] != nullptr)
		{
			this->particles[i]->draw(camera);
		}
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
		pDx = 0.05;
		pDy = -0.5;
		if(pX < this->x + 5 || pX > this->x + 20)
		{
			lifeTime = (400 + rand() % 1000);
		}
		else
		{
			lifeTime = (400 + rand() % 1600);
		}

		width = 3;
		height = 3;

		break;
	case PARTICLETYPES::SNOW:
		pDx = -0.05;
		pDy = 3;
		lifeTime = 3000 + rand() % 1000;
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
	this->surfPixel = nullptr;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
}