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

	this->stopSpeed = 0.5;
	//this->moveSpeed = id;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;

	this->path = "front.bmp";

}

void Player::move(EnumDirection direction, double dt) {
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





	//switch(direction) {
	//case EnumDirection::North: 
	//	setY(getY() - (moveSpeed * dt));
	//	break;
	//case EnumDirection::South: 
	//	setY(getY() + (moveSpeed * dt));
	//	break;
	//case EnumDirection::West: 		
	//	setX(getX() - (moveSpeed * dt));
	//	break;
	//case EnumDirection::East: 
	//	setX(getX() + (moveSpeed * dt));
	//	break;

	//}

}

void Player::draw(SDLInitializer* sdlInitializer) {
	//std::string path = "front.bmp";



	SDL_Surface*  img = SDL_LoadBMP(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlInitializer->getRenderer(), img);

	SDL_Rect rect;
	rect.w = 50;
	rect.h = 50;
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
