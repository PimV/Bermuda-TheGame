#include "Entity.h"
#include <cmath>

#include <iostream>

Entity::Entity(int id, int x, int y, int chunkSize)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->setChunkSize(chunkSize);

}

#pragma region Setters
void Entity::setX(double x) {
	this->x = x;
}

void Entity::setY(double y) {
	this->y = y;
}

void Entity::setZ(double z) {
	this->z = z;
}

void Entity::setTempX(double x) {
	this->tempX = x;
}

void Entity::setTempY(double y) {
	this->tempY = y;
}

void Entity::setWidth(double width) {
	this->width = width;
}

void Entity::setHeight(double height) {
	this->height = height;
}

void Entity::setChunkSize(int chunkSize)
{
	this->chunkSize = chunkSize;
	setChunks();
}

void Entity::setChunks()
{
	this->chunkY = floor(this->y / this->chunkSize);
	this->chunkX = floor(this->x / this->chunkSize);
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

int Entity::getChunkY()
{
	return this->chunkY;
}

int Entity::getChunkX()
{
	return this->chunkX;
}

int Entity::getChunkSize()
{
	return this->chunkSize;
}

#pragma endregion

Entity::~Entity(void)
{
}
