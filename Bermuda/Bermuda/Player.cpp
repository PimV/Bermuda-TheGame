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
	this->maxSpeed = 4;
	//this->maxSpeed = 0;

	//Berekening van collisionx verbeterd! DIT IS JUISTE VERSIE
	//	this->setCollisionWidth(this->getWidth()/4);
	//  this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
	//MERGE DEZE JUISTE VERSIE NIET WEG
	this->setCollisionHeight(this->getHeight() - 15);
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

	this->path = "Player_Dagger.png";
	this->playerAnimationWalkUp = 8, this->playerAnimationWalkLeft = 9;
	this->playerAnimationWalkDown = 10, this->playerAnimationWalkRight = 11;
	this->currentPlayerAnimationRow = this->playerAnimationWalkDown;
	this->playerAnimationIdle = 0; this->playerAnimationWalkStart = 1, this->playerAnimationWalkEnd = 7;
	this->frameAmountX = 0, this->frameAmountY = 0, this->CurrentFrame = 0;
	this->animationSpeed = 0, this->animationDelay = 1;

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
	if (this->moveClick)
	{
		this->movingLeft = false;
		this->movingRight = false;
		this->movingDown = false;
		this->movingUp = false;
		this->moveClick = false;
		StopAnimation();
	}
}

bool Player::checkCollision(CollidableContainer* container) {
	this->mapX = this->tempX;
	this->mapY = this->tempY;
	for (Collidable* c : container->getContainer()) {
		if (this->intersects(c)) {
			this->mapX = this->getX();
			this->mapY = this->getY();
			this->StopAnimation();
			return true;
		}
	}
	return false;
}

void Player::move(double dt) {

	if(moveClick)
	{
		//clickMove(NULL);		
		double angle = atan2(this->destY - this->getY(), this->destX - this->getX());
		// get 360° for the circle
		angle = (angle * (180/3.14) + 180);
		clickMove(dt, angle, this->getDistence(this->getX(), this->getY(), destX, destY));
	}
	else {
	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
				dx = -maxSpeed *dt;
		}
	} else if (movingRight) {
		dx += moveSpeed *dt;
			if (dx > maxSpeed *dt) {
				dx = maxSpeed *dt;
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
			if (dy < -maxSpeed *dt) {
				dy = -maxSpeed *dt;
		}
	} else if (movingDown) {
		dy += moveSpeed *dt;
			if (dy > maxSpeed *dt) {
				dy = maxSpeed *dt;
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
			
			//dx = dx / (moveSpeed / 2);
			//dy = dy / (moveSpeed / 2);
	}

	//Move player
	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);

	/*this->setX(getX() + dx);
	this->setY(getY() + dy);*/

	//Temp:
	//this->mapX = this->getX();
	//this->mapY = this->getY();

	//Move camera

		// set animation row
		if (this->movingLeft)
			this->currentPlayerAnimationRow = this->playerAnimationWalkLeft;
		else if (this->movingRight)
			this->currentPlayerAnimationRow = this->playerAnimationWalkRight;
		else if (this->movingUp)
			this->currentPlayerAnimationRow = this->playerAnimationWalkUp;
		else if (this->movingDown)
			this->currentPlayerAnimationRow = this->playerAnimationWalkDown;

		PlayAnimation(this->playerAnimationWalkStart,this->playerAnimationWalkEnd,this->currentPlayerAnimationRow, dt);
	}
	}

void Player::setPosition() {
	this->setX(getX() + dx);
	this->setY(getY() + dy);

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

double Player::getDistence(int currentX, int currentY, int destX, int destY)
	{
	double DifferenceX = currentX - destX;
	double DifferenceY = currentY - destY;
	return sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	}

void Player::clickMove(double dt, double angle, double distance) {
	
	int anime = 10;
	if (distance >= 2)
	{
		if (this->getX() != destX)
			this->setX( this->getX() -  ((this->getX()-destX)/distance) * (maxSpeed / 1.5) );
		if (this->getY() != destY)
			this->setY( this->getY() -  ((this->getY()-destY)/distance) * (maxSpeed / 1.5) );

		// Determine player walking animation sprite by the destenation angle
		/*
		if(angle > 45 && angle <= 135) // UP
			anime = this->playerAnimationWalkUp;
		else if(angle > 135 && angle <= 225) // Right
			anime = this->playerAnimationWalkRight;
		else if(angle > 225 && angle <= 315) // Down
			anime = this->playerAnimationWalkDown;
		else if( (angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45)) // Left
			anime = this->playerAnimationWalkLeft;
		*/
		
		if(angle > 60 && angle <= 120) // UP
			anime = this->playerAnimationWalkUp;
		else if(angle > 120 && angle <= 240) // Right
			anime = this->playerAnimationWalkRight;
		else if(angle > 240 && angle <= 300) // Down
			anime = this->playerAnimationWalkDown;
		else if( (angle <= 360 && angle > 300) || (angle >= 0 && angle <= 60)) // Left
			anime = this->playerAnimationWalkLeft;

		this->PlayAnimation(this->playerAnimationWalkStart,this->playerAnimationWalkEnd, anime, dt);
	}
	else
	{
		this->resetMovement();
	}
}

void Player::LoadSpriteSheet(std::string path, SDL_Renderer *renderer)
{
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
	{
		std::cout << "Coudn't load: " << path.c_str();
	}

	StopAnimation();
}

void Player::SetupAnimation(int amountFrameX, int amountFrameY)
{
	frameAmountX = amountFrameX, frameAmountY = amountFrameY;
	
	// Set width and height of the crop rect. The rest of is calculated in PlayAnimation()
	crop.w = this->getWidth();
	crop.h = this->getHeight();
}

void Player::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt)
{
	double animationDelay = (maxSpeed / 100)  * 40;
	animationSpeed -= animationDelay;
	if ( animationSpeed < animationDelay)
{
		this->currentPlayerAnimationRow = Row;
	if (EndFrame <= CurrentFrame)
		CurrentFrame = BeginFrame;
	else
		CurrentFrame++;

	crop.x = CurrentFrame * this->getWidth();
	crop.y = Row * this->getHeight();
		animationSpeed = maxSpeed * 3;
	}
	
}

void Player::StopAnimation()
{
	crop.x = playerAnimationIdle * this->getWidth();
	crop.y = this->currentPlayerAnimationRow * this->getHeight();
}

void Player::draw(SDLInitializer* sdlInitializer) {

	if (texture == NULL) {
		std::cout << "NO PLAYER IMAGE" << std::endl;
	}
	
	SDL_Rect rect;
	rect.w = this->getWidth();
	rect.h = this->getHeight();
	rect.x = getX() - this->camera->getX();
	rect.y = getY() - this->camera->getY();

	sdlInitializer->drawTexture(texture, &rect, &crop);
}

Player::~Player(void)
{
	SDL_DestroyTexture(texture);
}