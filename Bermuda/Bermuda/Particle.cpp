#include "Particle.h"
#include "GameStateManager.h"
#include "GameTimer.h"


Particle::Particle(double x, double y, double dx, double dy, int life, SDL_Texture* textPixel, int width, int height)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->textPixel = textPixel;
	this->endTime = GameTimer::Instance()->getGameTime() + life;
	
	rectPixel.w = width;
	rectPixel.h = height;
}


void Particle::move(double dt)
{
	this->x += this->dx * dt;
	this->y += this->dy * dt;
}

void Particle::draw(Camera* camera)
{
	rectPixel.x = static_cast<int>(this->x - camera->getX());
	rectPixel.y = static_cast<int>(this->y - camera->getY());
	GameStateManager::Instance()->sdlInitializer->drawTexture(textPixel, &rectPixel, NULL);

}

bool Particle::getIsDead()
{
	if(this->endTime < GameTimer::Instance()->getGameTime())
	{
		return true;
	}

	return false;
}


Particle::~Particle()
{
}