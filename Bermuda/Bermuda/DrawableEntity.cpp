#include "DrawableEntity.h"

double DrawableEntity::DRAWBUFFER = 64;

DrawableEntity::DrawableEntity(int id, double x, double y, Image* image) : 
	Entity(id,x,y), drawImage(image)
{
	if(image != nullptr)
	{
		setWidth(drawImage->getWidth());
		setHeight(drawImage->getHeight());
	}
	sizeRect = new SDL_Rect();
}

void DrawableEntity::draw(Camera* camera, SDL_Renderer* renderer)
{
	//Only draw if entity is inside the camera view and the buffer area
	if(	this->getEnabled() &&
		getX() + getWidth() > (camera->getX() - DRAWBUFFER) &&
		getX() < (camera->getX() + camera->getWidth() + DRAWBUFFER) &&
		getY() + getHeight() > (camera->getY() - DRAWBUFFER) &&
		getY() < (camera->getY() + camera->getHeight() + DRAWBUFFER))
	{
		sizeRect->x = getX() - camera->getX();
		sizeRect->y = getY() - camera->getY(); 
		sizeRect->w = getWidth();
		sizeRect->h = getHeight();
		
		//Draw the entity
		SDL_RenderCopy(renderer, drawImage->getTileSet(), drawImage->getCroppingRect(), sizeRect);
	}
}

void DrawableEntity::setDrawImage(Image* image)
{
	drawImage = image;
	if (this->getWidth() < 0 && this->getHeight() < 0)
	{
		setWidth(drawImage->getWidth());
		setHeight(drawImage->getHeight());
	}
}

DrawableEntity::~DrawableEntity()
{
	delete sizeRect;
}
