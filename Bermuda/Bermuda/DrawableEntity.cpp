#include "DrawableEntity.h"
#include <iostream>
double DrawableEntity::DRAWBUFFER = 64;

DrawableEntity::DrawableEntity(int id, double x, double y, Image* image) : 
	Entity(id,x,y), drawImage(image)
{
	if(image != nullptr)
	{
		this->setWidth(drawImage->getWidth());
		this->setHeight(drawImage->getHeight());
	}

	this->sizeRect = new SDL_Rect();
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
		sizeRect->x = static_cast<int>(getX() - camera->getX());
		sizeRect->y = static_cast<int>(getY() - camera->getY()); 
		sizeRect->w = static_cast<int>(getWidth());
		sizeRect->h = static_cast<int>(getHeight());

		//Draw the entity
		SDL_RenderCopy(renderer, drawImage->getTileSet(), drawImage->getCroppingRect(), sizeRect);
	}
}

void DrawableEntity::setDrawImage(Image* image)
{
	if (this->drawImage == nullptr)
	{
		this->setWidth(image->getWidth());
		this->setHeight(image->getHeight());
	}

	this->drawImage = image;
}

void DrawableEntity::setCanInteractTexture(SDL_Texture* can)
{
	this->canInteractTexture = can;
}

void DrawableEntity::setCantInteractTexture(SDL_Texture* cant)
{
	this->cantInteractTexture = cant;
}

SDL_Texture* DrawableEntity::getCanInteractTexture()
{
	return this->canInteractTexture;
}
SDL_Texture* DrawableEntity::getCantInteractTexture()
{
	return this->cantInteractTexture;
}

DrawableEntity::~DrawableEntity()
{
	delete sizeRect;
}
