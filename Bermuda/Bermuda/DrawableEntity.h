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
	Image* drawImage;
public:
	DrawableEntity(int id, Image* image);
	void draw(Camera* camera, SDL_Renderer* renderer);
	void setDrawImage(Image* image);
	virtual ~DrawableEntity();
};

