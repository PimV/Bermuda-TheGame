#include "Particle.h"
#include "GameStateManager.h"


Particle::Particle(float x, float y, float dx, float dy, int life, SDL_Texture* textPixel, int width, int height)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->textPixel = textPixel;
	this->endTime = SDL_GetTicks() + life;

	this->isDead = false;

	rectPixel.w = width;
	rectPixel.h = height;
}


void Particle::move(double dt)
{
	this->x += this->dx * dt;
	this->y += this->dy * dt;

	//Left
	if(this->x < 0)
	{
		this->x = 0;
		this->isDead = true;
	}

	//Top
	if(this->y < 0)
	{
		this->y = 0;
		this->isDead = true;
	}

	//Right
	if(this->x >= ScreenWidth)
	{
		this->x = ScreenWidth -1;
		this->isDead = true;
	}

	//Down
	if(this->y >= ScreenHeight)
	{
		this->y = ScreenHeight -1;
		this->isDead = true;
	}
}

void Particle::draw()
{
	rectPixel.x = this->x;
	rectPixel.y = this->y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(textPixel, &rectPixel, NULL);

}

bool Particle::getIsDead()
{
	if(this->isDead || SDL_GetTicks() >= endTime)
	{
		return true;
	}

	return false;
}


Particle::~Particle()
{
}
