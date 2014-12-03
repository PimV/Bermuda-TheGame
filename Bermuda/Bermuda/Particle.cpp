#include "Particle.h"
#include "GameStateManager.h"
#include "GameTimer.h"


Particle::Particle(float x, float y, float dx, float dy, int life, SDL_Texture* textPixel, int width, int height)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->textPixel = textPixel;
	this->endTime = GameTimer::Instance()->getGameTime() + life;

	this->isDead = false;

	rectPixel.w = width;
	rectPixel.h = height;
}


void Particle::move(double dt)
{
	this->x += this->dx * dt * GameStateManager::Instance()->getSpeedMultiplier();
	this->y += this->dy * dt * GameStateManager::Instance()->getSpeedMultiplier();

	//Check if outside of screen
	/*if(this->x < 0 || this->x >= ScreenWidth || this->y < 0 || this->y >= ScreenHeight)
	{
		this->isDead = true;
	}*/
}

void Particle::draw(Camera* camera)
{
	rectPixel.x = this->x - camera->getX();
	rectPixel.y = this->y - camera->getY();
	GameStateManager::Instance()->sdlInitializer->drawTexture(textPixel, &rectPixel, NULL);

}

bool Particle::getIsDead()
{
	if(this->isDead || endTime < GameTimer::Instance()->getGameTime())
	{
		return true;
	}

	return false;
}


Particle::~Particle()
{
}