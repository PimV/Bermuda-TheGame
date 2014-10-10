#include "Collidable.h"
#include <iostream>


Collidable::Collidable(double collisionX, double collisionY, double collisionWidth, double collisionHeight)
{
	this->collisionHeight = collisionHeight;
	this->collisionWidth = collisionWidth;
	this->collisionX = collisionX;
	this->collisionY = collisionY;

}

Collidable::Collidable() {

}

#pragma region Setters
void Collidable::setCollisionHeight(double collisionHeight) {
	this->collisionHeight = collisionHeight;
}
void Collidable::setCollisionWidth(double collisionWidth) {
	this->collisionWidth = collisionWidth;
}
void Collidable::setCollisionX(double collisionX) {
	this->collisionX = collisionX;
}
void Collidable::setCollisionY(double collisionY) {
	this->collisionY = collisionY;
}
#pragma endregion
#pragma region Getters
double Collidable::getCollisionHeight() {
	return this->collisionHeight;
}
double Collidable::getCollisionWidth() {
	return this->collisionWidth;
}
double Collidable::getCollisionX() {
	return this->collisionX;
}
double Collidable::getCollisionY() {
	return this->collisionY;
}
#pragma endregion

bool Collidable::intersects(Collidable* collidable) {
	double targetLeft = collidable->mapX + collidable->getCollisionX();
	double targetRight = collidable->mapX + collidable->getCollisionX() + collidable->getCollisionWidth();
	double targetTop = collidable->mapY + collidable->getCollisionY();
	double targetBot = collidable->mapY + collidable->getCollisionY() + collidable->getCollisionHeight();


	double thisLeft = this->mapX + this->getCollisionX();
	double thisRight = this->mapX + this->getCollisionX() + this->getCollisionWidth();
	double thisTop = this->mapY + this->getCollisionY() + this->mapHeight;
	double thisBot = this->mapY + this->getCollisionY() + this->getCollisionHeight();



	if (((thisLeft < targetRight && thisLeft > targetLeft) || (thisRight > targetLeft && thisRight < targetRight))
		&&
		((thisTop < targetBot && thisTop > targetTop) || (thisBot > targetTop && thisBot < targetBot))) {
			return true;
	}
	return false;
}

Collidable::~Collidable()
{
}
