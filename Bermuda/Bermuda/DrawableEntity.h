#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "Image.h"

class DrawableEntity :
	public Entity
{
private:
	const double DRAWBUFFER;
	Image* image;
public:
	DrawableEntity(int id, Image* image);
	void draw(Camera* camera, SDL_Renderer* renderer);
	virtual ~DrawableEntity();
};

