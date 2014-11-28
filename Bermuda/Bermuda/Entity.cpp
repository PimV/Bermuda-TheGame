#include "Entity.h"
#include "MainEntityContainer.h"
#include <cmath>

#include <iostream>

Entity::Entity(int id, double x, double y, int chunkSize)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->setChunkSize(chunkSize);
	this->setEnabled(true);
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

void Entity::setWidth(double width) {
	this->width = width;
}

void Entity::setHeight(double height) {
	this->height = height;
}

void Entity::setChunkSize(int chunkSize)
{
	this->chunkSize = chunkSize;
	this->setChunks();
}

void Entity::setMainEntityContainer(MainEntityContainer* mec) {
	this->mec = mec;
}

void Entity::setChunks()
{
	this->chunkY = floor(this->y / this->chunkSize);
	this->chunkX = floor(this->x / this->chunkSize);
}
void Entity::setEnabled(bool enabled)
{
	this->enabled = enabled;
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

MainEntityContainer* Entity::getMainEntityContainer() {
	return this->mec;
}

bool Entity::getEnabled()
{
	return this->enabled;
}
#pragma endregion

Entity::~Entity(void)
{
}
