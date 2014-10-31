#include "Rabbit.h"
#include <time.h>
#include <iostream>

Rabbit::Rabbit(int id, int chunkSize, Spawnpoint* spawnPoint, GameStateManager* gsm, MainEntityContainer* mec) :
	NPC(id, chunkSize, 5, 1, 20, 5, spawnPoint),
	Entity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize),
	DrawableEntity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize, nullptr),
	//CollidableEntity(id, x, y, chunkSize, 34, 102, 27, 15), mec(mec), treeImage(treeImage), stumpImage(stumpImage)
	IMovable(moveSpeed)
{
	this->tempCounter = 0;
	this->walking = false;

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->stopSpeed = 0.8;

	this->setTempX(this->getX());
	this->setTempY(this->getY());


	this->setMainEntityContainer(mec);
	//this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	//this->getMainEntityContainer()->getCollidableContainer()->add(this);

	//this->movingLeft = false;
	//this->movingRight = false;
	//this->movingDown = false;
	//this->movingUp = false;
	//this->moveClick = false;
	//this->interaction = false;

	this->firstImgID = gsm->getImageLoader()->loadTileset("rabbitsheet.png", 40, 40);

	//this->playerAnimationWalkUpRow = 8, this->playerAnimationWalkLeftRow = 9;
	//this->playerAnimationWalkDownRow = 10, this->playerAnimationWalkRightRow = 11;
	//this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;
	//this->playerAnimationIdleColumn = 0; this->playerAnimationWalkStartColumn = 1, this->playerAnimationWalkEndColumn = 8;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	//this->frameAmountX = 13, this->frameAmountY = 21, this->CurrentFrame = 0;
	//this->animationSpeed = 10;//, this->animationDelay = 1;

	//Set camera
	//this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	//this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	//this->StopAnimation();

	//Add to containers
	mec->getDrawableContainer()->add(this);

}

void Rabbit::walk(double dt)
{
	walking = false;
	if (walking == false) {
		walking = true;

		srand(time(NULL));

		double distanceX = rand() % (this->getWalkRange() * 2) + (this->getWalkRange() * -1);
		double distanceY = rand() % (this->getWalkRange() * 2) + (this->getWalkRange() * -1);

		double destinationX = this->getSpawnPoint()->getX() + distanceX;
		double destinationY = this->getSpawnPoint()->getY() + distanceY;

		this->move(dt, destinationX, destinationY);

		walking = false;
	}
}

void Rabbit::move(double dt, double destinationX, double destinationY)
{
	if (this->getX() + this->getWidth() / 2 > destinationX - 5 && this->getX() + this->getWidth() / 2  < destinationX + 5) {
		movingRight = false;
		movingLeft = false;
	}
	else if (destinationX > this->getX() + this->getWidth() / 2)
	{
		movingRight = true;
		movingLeft = false;
	}
	else if (destinationX < this->getX() + this->getWidth() / 2)
	{
		movingLeft = true;
		movingRight = false;
	}

	if (this->getY() + this->getHeight() > destinationY - 5 && this->getY() + this->getHeight() < destinationY + 5) {
		movingDown = false;
		movingUp = false;
	}
	else if (destinationY > this->getY() + this->getHeight())
	{
		movingDown = true;
		movingUp = false;
	}
	else if (destinationY < this->getY() + this->getHeight())
	{
		movingUp = true;
		movingDown = false;
	}


	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed *dt;
		}
	}
	else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed *dt) {
			dx = maxSpeed *dt;
		}
	}
	else {
		if (dx > 0) {
			dx -= stopSpeed *dt;
			if (dx < 0) {
				dx = 0;
			}
		}
		else if (dx < 0) {
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
	}
	else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed *dt) {
			dy = maxSpeed *dt;
		}
	}
	else {
		if (dy > 0) {
			dy -= stopSpeed *dt;
			if (dy < 0) {
				dy = 0;
			}
		}
		else if (dy < 0) {
			dy += stopSpeed *dt;
			if (dy > 0) {
				dy = 0;
			}
		}
	}

	if (dx == 0 && dy == 0) {
		return;
	}

	//if (dx != 0 && dy != 0) {

	//dx = dx / 2;
	//dy = dy / 2;

	//dx = dx / (moveSpeed / 2);
	//dy = dy / (moveSpeed / 2);
	//}

	//Move player
	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);

}

void Rabbit::update(double dt) {
	this->tempCounter++;
	std::cout << tempCounter;
	if (this->tempCounter == 1000) {
		std::cout << "Rabbit is walking!";
		this->walk(dt);
	}

	//if (destroyed) {
	//	this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
	//	if (this->timeSinceDestroy > respawnTime) {
	//		this->respawn();
	//	}
	//}
}


Rabbit::~Rabbit()
{

}