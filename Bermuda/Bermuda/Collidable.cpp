#include "Collidable.h"


Collidable::Collidable(double collisionX, double collisionY, double collisionWidth, double collisionHeight)
{
	this->collisionHeight = collisionHeight;
	this->collisionWidth = collisionWidth;
	this->collisionX = collisionX;
	this->collisionY = collisionY;
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


Collidable::~Collidable()
{
}
