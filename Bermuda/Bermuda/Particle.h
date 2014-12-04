#pragma once
#include "header_loader.h"
#include "Camera.h"

class Particle
{
private:
	float x;
	float y;
	float dx;
	float dy;

	bool isDead;

	long endTime;

	
	SDL_Texture* textPixel;
	SDL_Rect rectPixel;

public:
	Particle(float x, float y, float dx, float dy, int life, SDL_Texture* textPixel, int width, int height);
	virtual ~Particle();

	void move(double dt);
	void draw(Camera* camera);
	bool getIsDead();

};