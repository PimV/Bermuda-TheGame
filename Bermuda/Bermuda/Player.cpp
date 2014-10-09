#include "Player.h"
#include <iostream>


Player::Player(int id, double moveSpeed, Camera* camera)
	: Entity(id), IMovable(moveSpeed)
{

	this->camera = camera;

	//TODO: Change setx and sety to spawnlocation
	this->setX(350);
	this->setY(350);
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 6;

	this->setWidth(31);
	this->setHeight(48);

	this->setCollisionHeight(this->getHeight());
	this->setCollisionWidth(this->getWidth()/2);
	this->setCollisionX(this->getWidth()/4);
	this->setCollisionY(0);

	this->mapHeight = this->getHeight();
	this->mapWidth = this->getWidth();
	this->mapX = this->getX();
	this->mapY = this->getY();

	this->stopSpeed = 0.8;
	//this->moveSpeed = id;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;

	this->path = "F.png";


	//Set camera
	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

void Player::resetMovement()
{
	if (moveClick) {
		this->movingLeft = false;
		this->movingRight = false;
		this->movingDown = false;
		this->movingUp = false;
		this->moveClick = false;
	}
}

bool Player::checkCollision(CollidableContainer* container) {
	this->mapX = this->tempX;
	this->mapY = this->tempY;
	for (Collidable* c : container->getContainer()) {
		if (this->intersects(c)) {
			this->mapX = this->getX();
			this->mapY = this->getY();
			return true;
		}
	}
	return false;
}

void Player::move(double dt) {

	if(moveClick)
	{
		clickMove();		
	}

	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed;
		}
	} else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed*dt) {
			dx = maxSpeed;
		}
	} else {
		if (dx > 0) {
			dx -= stopSpeed *dt;
			if (dx < 0) {
				dx = 0;
			}
		} else if (dx < 0) {
			dx += stopSpeed *dt;
			if (dx > 0) {
				dx = 0;
			}
		}
	}

	if (movingUp) {
		dy -= moveSpeed *dt;
		if (dy < -maxSpeed*dt) {
			dy = -maxSpeed;
		}
	} else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed*dt) {
			dy = maxSpeed;
		}
	} else {
		if (dy > 0) {
			dy -= stopSpeed *dt;
			if (dy < 0) {
				dy = 0;
			}
		} else if (dy < 0) {
			dy += stopSpeed *dt;
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

	dx = dx*dt;
	dy = dy*dt;

	//Move player


	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);

	/*this->setX(getX() + dx);
	this->setY(getY() + dy);*/

	//Temp:
	//this->mapX = this->getX();
	//this->mapY = this->getY();

	//Move camera



	if (this->movingLeft) {
		path = "L.png";
	}
	else if (this->movingRight) {
		path = "R.png";
	}
	else if (this->movingUp) {
		path = "B.png";
	}
	else if (this->movingDown) {
		path = "F.png";
	}
}

void Player::setPosition() {
	this->setX(getX() + dx);
	this->setY(getY() + dy);

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
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

	SDL_Texture* texture = IMG_LoadTexture(sdlInitializer->getRenderer(), path);

	if (texture == NULL) {
		std::cout << "NO IMAGE" << std::endl;
	}

	//SDL_Surface*  img = SDL_LoadBMP(path);
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlInitializer->getRenderer(), img);

	SDL_Rect rect;
	rect.w = this->getWidth();
	rect.h = this->getHeight();
	rect.x = getX() - this->camera->getX();
	rect.y = getY() - this->camera->getY();

	//Add texture to renderer

	sdlInitializer->drawTexture(texture, &rect);

	//	sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	//SDL_FreeSurface(img); 
}

Player::~Player(void)
{
}