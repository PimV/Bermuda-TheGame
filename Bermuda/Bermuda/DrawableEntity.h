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
		
	SDL_Texture* canInteractTexture;
	SDL_Texture* cantInteractTexture;

public:
	DrawableEntity(int id, double x, double y, Image* image);
	virtual void draw(Camera* camera, SDL_Renderer* renderer);
	void setDrawImage(Image* image);
		
	void setCanInteractTexture(SDL_Texture* can);
	void setCantInteractTexture(SDL_Texture* cant);
	SDL_Texture* getCanInteractTexture();
	SDL_Texture* getCantInteractTexture();

	virtual ~DrawableEntity();
};

