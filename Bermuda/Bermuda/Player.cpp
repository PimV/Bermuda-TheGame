#include "Player.h"
#include "header_loader.h"
#include <iostream>
#include "Inventory.h"


Player::Player(int id, double moveSpeed, Camera* camera, GameStateManager* gsm, MainEntityContainer* mec)
	: Entity(id), DrawableEntity(id, nullptr), CollidableEntity(id), IMovable(moveSpeed)
{
	this->camera = camera;
	this->gsm = gsm;

	//TODO: Change setx and sety to spawnlocation
	this->setX(350);
	this->setY(350);
	this->setWidth(64);
	this->setHeight(64);
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	//this->maxSpeed = 0;

	this->playerTimer = new PlayerUpdateTimer();
	this->health = 100, this->hunger = 100, this->thurst = 100;

	this->setCollisionHeight(this->getHeight() - 15);
	this->setCollisionWidth(this->getWidth()/4);
	this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
	this->setCollisionY(0);

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;

	this->firstImgID = gsm->getImageLoader()->loadTileset("Player_Dagger.png", 64, 64);
	this->playerAnimationWalkUpRow = 8, this->playerAnimationWalkLeftRow = 9;
	this->playerAnimationWalkDownRow = 10, this->playerAnimationWalkRightRow = 11;
	this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;
	this->playerAnimationIdleColumn = 0; this->playerAnimationWalkStartColumn = 1, this->playerAnimationWalkEndColumn = 8;
	this->frameAmountX = 13, this->frameAmountY = 21, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->StopAnimation();
	mec->getDrawableContainer()->add(this);

	//Set camera
	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	this->inventory = new Inventory();
}

Inventory* Player::getInventory() {
	return this->inventory;
}

void Player::resetMovement() {
	if (this->moveClick) {
		this->movingLeft = false;
		this->movingRight = false;
		this->movingDown = false;
		this->movingUp = false;
		this->moveClick = false;
		StopAnimation();
	}
}

bool Player::checkCollision(CollidableContainer* container) {
	double currentX = this->getX();
	double currentY = this->getY();
	this->setX(this->tempX);
	this->setY(this->tempY);
	for (CollidableEntity* c : container->getContainer()) {
		if (this->intersects(c)) {
			this->setX(currentX);
			this->setY(currentY);
			this->StopAnimation();
			return true;
		}
	}
	return false;
}

void Player::update(double dt) {
	this->updatePlayerStatuses();
	this->move(dt);
}

#pragma region PlayerStatusUpdates
void Player::updatePlayerStatuses()
{
	this->playerTimer->updateGameTime(this->gsm->lastUpdateLength);

	if ( playerTimer->updateHungerTime() )
	{
		if (this->getHunger() > 0)
			this->updateHunger(-1);
		else 
			this->updateHealth(-1);
	}

	if ( playerTimer->updateThurstTime() )
	{
		if (this->getThurst() > 0)
			this->updateThurst(-1);
		else
			this->updateHealth(-2);
	}

	/*
	this->gsm->sdlInitializer->drawText(std::string("Health: " + to_string(this->getHealth())), 5, 5, 100, 25);
	this->gsm->sdlInitializer->drawText(std::string("Hunger: " + to_string(this->getHunger())), 5, 5, 100, 25);
	this->gsm->sdlInitializer->drawText(std::string("Thurst: " + to_string(this->getThurst())), 5, 5, 100, 25);
	*/
	
}

void Player::updateHealth(int value)
{
	if ( (this->health + value)  > 100)
		this->health = 100;
	else
		this->health += value;
}

void Player::updateHunger(int value)
{
	if ( (this->hunger + value)  > 100)
		this->hunger = 100;
	else if ( (this->health - value)  < 0 )
		this->hunger = 0;
	else
		this->hunger += value;
	
	//std::cout << "Hunger: " << this->hunger << std::endl;
}

void Player::updateThurst(int value)
{
	if ( (this->thurst + value)  > 100)
		this->thurst = 100;
	else if ( (this->health - value)  < 0 )
		this->hunger = 0;
	else
		this->thurst += value;

	//std::cout << "Thurst: " << this->thurst << std::endl;
}

int Player::getHealth()
{
	return this->health;
}

int Player::getHunger()
{
	return this->hunger;
}

int Player::getThurst()
{
	return this->thurst;
}
#pragma endregion PlayerStatusUpdates

void Player::move(double dt) {

	if(moveClick) {
		clickMove();
	}

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

		//dx = dx / 2;
		//dy = dy / 2;

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
		this->currentPlayerAnimationRow = this->playerAnimationWalkLeftRow;
	else if (this->movingRight)
		this->currentPlayerAnimationRow = this->playerAnimationWalkRightRow;
	else if (this->movingUp)
		this->currentPlayerAnimationRow = this->playerAnimationWalkUpRow;
	else if (this->movingDown)
		this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;

	PlayAnimation(this->playerAnimationWalkStartColumn,this->playerAnimationWalkEndColumn,this->currentPlayerAnimationRow, dt);

}

void Player::setPosition() {
	//this->setX(getX() + dx);
	//this->setY(getY() + dy);

	this->setX(this->tempX);
	this->setY(this->tempY);

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

double Player::getDistence(int currentX, int currentY, int destX, int destY)
{
	double DifferenceX = currentX - destX;
	double DifferenceY = currentY - destY;
	return sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
}

void Player::clickMove() {

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

void Player::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) {
	double animationDelay = (maxSpeed / 100)  * 40;
	animationSpeed -= animationDelay;
	if ( animationSpeed < animationDelay) {
		this->currentPlayerAnimationRow = Row;
		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + CurrentFrame));
		animationSpeed = maxSpeed * 3;
	}

}

void Player::StopAnimation() {
	this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + playerAnimationIdleColumn));
}


Player::~Player(void) {
	delete this->inventory;
}