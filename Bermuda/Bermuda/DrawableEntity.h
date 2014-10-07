#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "Image.h"

class DrawableEntity :
	public Entity
{
protected:
	virtual Image* image;
public:
	DrawableEntity(int id);
	void draw(Camera camera, SDL_Renderer* renderer);
	virtual ~DrawableEntity();
};

