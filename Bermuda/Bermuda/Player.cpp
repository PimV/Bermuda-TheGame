#include "Player.h"
#include <iostream>


Player::Player(int id, double moveSpeed, Camera* camera)
	: Entity(id), IMovable(moveSpeed)
{

	this->camera = camera;

	//TODO: Change setx and sety to spawnlocation
	this->setX(350);
	this->setY(350);
	this->setWidth(64);
	this->setHeight(64);
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 6;

	//Berekening van collisionx verbeterd! DIT IS JUISTE VERSIE
	//	this->setCollisionWidth(this->getWidth()/4);
	//  this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
	//MERGE DEZE JUISTE VERSIE NIET WEG
	this->setCollisionHeight(this->getHeight());
	this->setCollisionWidth(this->getWidth()/4);
	this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
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

	//this->path = "F.png";
	this->path = "Player_Dagger.png";
	this->frameAmountX = 0, this->frameAmountY = 0, this->CurrentFrame = 0;
	crop.x = 0;
	crop.y = 0;
	crop.w = 0;
	crop.h = 0;

	// amount of sprites in the sheet
	this->SetupAnimation(13, 21);
	
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
		PlayAnimation(1,7,9,0);
	}
	else if (this->movingRight) {
		PlayAnimation(1,7,11,0);
	}
	else if (this->movingUp) {
		PlayAnimation(1,7,8,0);
	}
	else if (this->movingDown) {
		PlayAnimation(1,7,10,0);
	}
}

void Player::setPosition() {
	this->setX(getX() + dx);
	this->setY(getY() + dy);

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

void Player::clickMove(){
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

void Player::LoadSpriteSheet(std::string path, SDL_Renderer *renderer)
{
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
	{
		std::cout << "Coudn't load: " << path.c_str();
	}

	PlayAnimation(1,1,10,0);
}

void Player::SetupAnimation(int amountFrameX, int amountFrameY)
{
	frameAmountX = amountFrameX, frameAmountY = amountFrameY;
	
	// The rest of is calculated in PlayAnimation()
	crop.w = this->getWidth();///frameAmountX;
	crop.h = this->getHeight();///frameAmountY;
}

void Player::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (EndFrame <= CurrentFrame)
		CurrentFrame = BeginFrame;
	else
		CurrentFrame++;

	//crop.x = CurrentFrame * (this->getWidth()/frameAmountX);
	crop.x = CurrentFrame * this->getWidth();
	//crop.y = Row * (this->getHeight()/frameAmountY);
	crop.y = Row * this->getHeight();
	// The rest is set in SetupAnimation(), for is doesn't change
}

void Player::StopAnimation(int Row)
{
	this->PlayAnimation(0, 0, Row, 0);
}

void Player::draw(SDLInitializer* sdlInitializer) {
	//std::string path = "front.bmp";

	//SDL_Texture* texture = IMG_LoadTexture(sdlInitializer->getRenderer(), path.c_str());

	if (texture == NULL) {
		std::cout << "NO PLAYER IMAGE" << std::endl;
	}
	
	//std::cout<< this->getWidth() << std::endl;

	SDL_Rect rect;
	rect.w = this->getWidth();// /frameAmountX;
	rect.h = this->getHeight();// /frameAmountY;
	rect.x = getX() - this->camera->getX();
	rect.y = getY() - this->camera->getY();

	/*rect.w = crop.w;
	rect.h = crop.h;
	rect.x = crop.x;
	rect.y = crop.y;*/
	
	//Add texture to renderer

	sdlInitializer->drawTexture(texture, &rect, &crop);

		sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	//SDL_DestroyTexture(texture);  
	//SDL_FreeSurface(img); 
}

Player::~Player(void)
{
	SDL_DestroyTexture(texture);
}