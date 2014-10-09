#include "DrawableEntity.h"


DrawableEntity::DrawableEntity(int id, Image* image)
	: Entity(id), DRAWBUFFER(64), drawImage(image)
{
	setWidth(drawImage->getWidth());
	setHeight(drawImage->getHeight());
}

void DrawableEntity::draw(Camera* camera, SDL_Renderer* renderer)
{
	//Only draw if entity is inside the camera view and the buffer area
	if((getX() + getWidth()) > (camera->getX() - DRAWBUFFER) &&
		getX() < (camera->getX() + camera->getWidth() + DRAWBUFFER) &&
		(getY() + getHeight()) > (camera->getY() - DRAWBUFFER) &&
		getY() < (camera->getY() + camera->getHeight() + DRAWBUFFER))
	{		
		sizeRect.x = getX() - camera->getX();
		sizeRect.y = getY() - camera->getY(); 
		sizeRect.w = getWidth();
		sizeRect.h = getHeight();

		//Draw the entity
		SDL_RenderCopy(renderer, drawImage->getTileSet(), drawImage->getCroppingRect(), &sizeRect);
	}
}

void DrawableEntity::setDrawImage(Image* image)
{
	drawImage = image;
}

DrawableEntity::~DrawableEntity()
{
}
