#include "DrawableEntity.h"


DrawableEntity::DrawableEntity(int id, Image* image)
	: Entity(id), DRAWBUFFER(64), drawImage(image)
{
	setWidth(image->getCroppingRect()->w);
	setHeight(image->getCroppingRect()->h);
}

void DrawableEntity::draw(Camera* camera, SDL_Renderer* renderer)
{
	//Only draw if entity is inside the camera view and the buffer area
	if((getX() + getWidth()) > (camera->getX() - DRAWBUFFER) &&
		getX() < (camera->getX() + camera->getWidth() + DRAWBUFFER) &&
		(getY() + getHeight()) > (camera->getY() - DRAWBUFFER) &&
		getY() < (camera->getY() + camera->getHeight() + DRAWBUFFER))
	{
		SDL_Rect rect;
		rect.x = getX() - camera->getX();
		rect.y = getY() - camera->getY(); 
		rect.w = getWidth();
		rect.h = getHeight();

		//Draw the entity
		SDL_RenderCopy(renderer, drawImage->getTileSet(), drawImage->getCroppingRect(), &rect);
	}
}

void DrawableEntity::setDrawImage(Image* image)
{
	drawImage = image;
}

DrawableEntity::~DrawableEntity()
{
}
