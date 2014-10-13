#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "Image.h"

class DrawableEntity :
	public Entity
{
private:
	static double DRAWBUFFER;
	Image* drawImage;
	SDL_Rect* sizeRect;
public:
	DrawableEntity(int id, Image* image);
	void draw(Camera* camera, SDL_Renderer* renderer);
	void setDrawImage(Image* image);
	virtual ~DrawableEntity();
};

