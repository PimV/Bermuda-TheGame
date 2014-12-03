#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "Image.h"

class DrawableEntity :
	public virtual Entity
{
private:
	static double DRAWBUFFER;
	Image* drawImage;
	SDL_Rect* sizeRect;
public:
	DrawableEntity(int id, double x, double y, Image* image);
	virtual void draw(Camera* camera, SDL_Renderer* renderer);
	void setDrawImage(Image* image);
	virtual ~DrawableEntity();
};

