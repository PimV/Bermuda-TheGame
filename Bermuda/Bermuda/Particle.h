#pragma once
#include "header_loader.h"
#include "Camera.h"

class Particle
{
private:
	double x;
	double y;
	double dx;
	double dy;

	bool isDead;

	float endTime;

	
	SDL_Texture* textPixel;
	SDL_Rect rectPixel;

public:
	Particle(double x, double y, double dx, double dy, int life, SDL_Texture* textPixel, int width, int height);
	virtual ~Particle();

	void move(double dt);
	void draw(Camera* camera);
	bool getIsDead();

};