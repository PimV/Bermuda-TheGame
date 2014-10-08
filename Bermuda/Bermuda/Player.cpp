#include "Player.h"
#include <iostream>


Player::Player(int id, double moveSpeed)
	: Entity(id), IMovable(moveSpeed)
{
	this->setX(100);
	this->setY(100);
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 5;

	this->setWidth(50);
	this->setHeight(50);

	this->stopSpeed = 0.5;
	//this->moveSpeed = id;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;

	this->path = "front.bmp";

}

void Player::resetMovement()
{
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;
}

void Player::move(double dt) {
	
	if(moveClick)
	{
		if (getX() == destX && getY() == destY) {
			moveClick = false;
		} else {
			clickMove();
		}
	}

	if (movingLeft) {
		dx -= moveSpeed;
		if (dx < -maxSpeed) {
			dx = -maxSpeed;
		}
	} else if (movingRight) {
		dx += moveSpeed;
		if (dx > maxSpeed) {
			dx = maxSpeed;
		}
	} else {
		if (dx > 0) {
			dx -= stopSpeed;
			if (dx < 0) {
				dx = 0;
			}
		} else if (dx < 0) {
			dx += stopSpeed;
			if (dx > 0) {
				dx = 0;
			}
		}
	}

	if (movingUp) {
		dy -= moveSpeed;
		if (dy < -maxSpeed) {
			dy = -maxSpeed;
		}
	} else if (movingDown) {
		dy += moveSpeed;
		if (dy > maxSpeed) {
			dy = maxSpeed;
		}
	} else {
		if (dy > 0) {
			dy -= stopSpeed;
			if (dy < 0) {
				dy = 0;
			}
		} else if (dy < 0) {
			dy += stopSpeed;
			if (dy > 0) {
				dy = 0;
			}
		}
	}

	if (dx == 0 && dy == 0) {
		return;
	}

	if (dx != 0 && dy != 0) {
		dx = dx / 2;
		dy = dy / 2;
	}

	this->setX(getX() + dx);
	this->setY(getY() + dy);

	
	if (this->movingLeft) {
		path = "left2.bmp";
	}
	else if (this->movingRight) {
		path = "right.bmp";
	}
	else if (this->movingUp) {
		path = "back.bmp";
	}
	else if (this->movingDown) {
		path = "front.bmp";
	}
}

void Player::clickMove(){
	std::cout << destX << " - " << destY << std::endl;
	std::cout << getX() << " get-get " << getY() << std::endl;

	if (this->getX() + this->getWidth() / 2 > this->destX - 5 && this->getX() + this->getWidth() / 2  < this->destX + 5) {
		movingRight = false;
		movingLeft = false;
	} else if(this->destX > this->getX() + this->getWidth() / 2)
	{
		movingRight = true;
		movingLeft = false;
	}
	else if(this->destX < this->getX() + this->getWidth() / 2)
	{
		movingLeft = true;
		movingRight = false;
	}

	if (this->getY() + this->getHeight() > this->destY - 5 && this->getY() + this->getHeight() < this->destY + 5) {
		movingDown = false;
		movingUp = false;
	} else if(this->destY > this->getY() + this->getHeight())
	{
		movingDown = true;
		movingUp = false;
	}
	else if(this->destY < this->getY() + this->getHeight())
	{
		movingUp = true;
		movingDown = false;
	}

	if (!movingDown && !movingUp && !movingLeft && !movingRight) {
		moveClick = false;
	}
}


void Player::draw(SDLInitializer* sdlInitializer) {
	//std::string path = "front.bmp";



	SDL_Surface*  img = SDL_LoadBMP(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlInitializer->getRenderer(), img);

	SDL_Rect rect;
	rect.w = this->getWidth();
	rect.h = this->getHeight();
	rect.x = getX();
	rect.y = getY();

	//Add texture to renderer

	sdlInitializer->drawTexture(texture, &rect);

	//	sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
}

Player::~Player(void)
{
}
