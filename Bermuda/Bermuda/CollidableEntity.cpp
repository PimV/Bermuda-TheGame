#include "CollidableEntity.h"
#include "PlayState.h"
#include "Camera.h"
#include <iostream>


CollidableEntity::CollidableEntity(int id, double x, double y, int chunkSize, double collisionX, double collisionY, double collisionWidth, double collisionHeight)
	: Entity(id,x,y,chunkSize)
{
	this->collisionHeight = collisionHeight;
	this->collisionWidth = collisionWidth;
	this->collisionX = collisionX;
	this->collisionY = collisionY;

	this->collidableTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelRed.png").c_str());
}

CollidableEntity::CollidableEntity(int id, double x, double y, int chunkSize)
	: Entity(id,x,y,chunkSize)
{
}

void CollidableEntity::drawCollidableArea()
{
	Camera* c = PlayState::Instance()->getCamera();

	collidableRect.x = this->getX() - c->getX() + this->getCollisionX();
	collidableRect.y = this->getY() - c->getY() + this->getCollisionY();
	collidableRect.w = this->getCollisionWidth();
	collidableRect.h = this->getCollisionHeight();

	GameStateManager::Instance()->sdlInitializer->drawTexture(this->collidableTexture,&this->collidableRect,NULL);
}

#pragma region Setters
void CollidableEntity::setCollisionHeight(double collisionHeight) {
	this->collisionHeight = collisionHeight;
}
void CollidableEntity::setCollisionWidth(double collisionWidth) {
	this->collisionWidth = collisionWidth;
}
void CollidableEntity::setCollisionX(double collisionX) {
	this->collisionX = collisionX;
}
void CollidableEntity::setCollisionY(double collisionY) {
	this->collisionY = collisionY;
}
#pragma endregion
#pragma region Getters
double CollidableEntity::getCollisionHeight() {
	return this->collisionHeight;
}
double CollidableEntity::getCollisionWidth() {
	return this->collisionWidth;
}
double CollidableEntity::getCollisionX() {
	return this->collisionX;
}
double CollidableEntity::getCollisionY() {
	return this->collisionY;
}
#pragma endregion

bool CollidableEntity::intersects(CollidableEntity* collidableEntity, MovableEntity* movableEntity) {
	if(this == collidableEntity)
	{
		return false;
	}

	double targetLeft = collidableEntity->getX() + collidableEntity->getCollisionX();
	double targetRight = collidableEntity->getX() + collidableEntity->getCollisionX() + collidableEntity->getCollisionWidth();
	double targetTop = collidableEntity->getY() + collidableEntity->getCollisionY();
	double targetBot = collidableEntity->getY() + collidableEntity->getCollisionY() + collidableEntity->getCollisionHeight();

	double thisLeft = this->getTempX() + this->getCollisionX();
	double thisRight = this->getTempX() + this->getCollisionX() + this->getCollisionWidth();
	double thisTop = this->getTempY() + this->getCollisionY();
	double thisBot = this->getTempY() + this->getCollisionY() + this->getCollisionHeight();

	if (thisLeft < targetRight &&
	thisRight > targetLeft &&
	thisTop < targetBot &&
	thisBot > targetTop)
	{
	return true;
	}

	/*if(movableEntity->getId() == 1)
	{
		if(movableEntity->movingUp && movableEntity->movingLeft)
		{
			std::cout << "UP-LEFT" << std::endl;
		}
		else if(movableEntity->movingUp && movableEntity->movingRight)
		{
			std::cout << "UP-RIGHT" << std::endl;
		}
		else if(movableEntity->movingDown && movableEntity->movingRight)
		{
			std::cout << "DOWN-RIGHT" << std::endl;
		}
		else if(movableEntity->movingDown && movableEntity->movingLeft)
		{
			std::cout << "DOWN-LEFT" << std::endl;
		}
		else if(movableEntity->movingUp)
		{
			std::cout << "UP" << std::endl;
		}
		else if(movableEntity->movingRight)
		{
			std::cout << "RIGHT" << std::endl;
		}
		else if(movableEntity->movingDown)
		{
			std::cout << "DOWN" << std::endl;
		}
		else if(movableEntity->movingLeft)
		{
			std::cout << "LEFT" << std::endl;
		}
	}*/

	return false;
}

CollidableEntity::~CollidableEntity()
{
	SDL_DestroyTexture(collidableTexture);
}
