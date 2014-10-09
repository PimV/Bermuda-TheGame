#include "Entity.h"
#include "header_loader.h"
#include <cmath>

Entity::Entity(int id)
{
	this->id = id;
}

#pragma region Setters
void Entity::setX(double x) {
	this->x = x * (ScreenHeight / OPTIMALRESOLUTIONH);
}

void Entity::setY(double y) {
	this->y = y * (ScreenHeight / OPTIMALRESOLUTIONH);
}

void Entity::setZ(double z) {
	this->z = z;
}

void Entity::setWidth(double width) {
	this->width = width;
}

void Entity::setHeight(double height) {
	this->height = height;
}
#pragma endregion
#pragma region Getters
int Entity::getId() {
	return this->id;
}

double Entity::getX() {
	return this->x;
}

double Entity::getY() {
	return this->y;
}

double Entity::getZ() {
	return this->z;
}

double Entity::getWidth() {
	return this->width;
}

double Entity::getHeight() {
	return this->height;
}

#pragma endregion

Entity::~Entity(void)
{
}
