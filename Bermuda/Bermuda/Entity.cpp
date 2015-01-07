#include "Entity.h"
#include "PlayState.h"
#include <cmath>

Entity::Entity(int id, double x, double y)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->setEnabled(true);
	this->setChunks();
	this->setHighlighted(false);
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

void Entity::setChunks()
{
	int chunkSize = PlayState::Instance()->getMainEntityContainer()->getChunkSize();
	this->chunkY = floor(this->y / chunkSize);
	this->chunkX = floor(this->x / chunkSize);
}

void Entity::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void Entity::setHighlighted(bool highlighted) {
	this->highlighted = highlighted;
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

double Entity::getCenterX()
{
	return this->x + this->width / 2;
}

double Entity::getCenterY()
{
	return this->y + this->height / 2;
}

int Entity::getChunkY()
{
	return this->chunkY;
}

int Entity::getChunkX()
{
	return this->chunkX;
}

bool Entity::getEnabled()
{
	return this->enabled;
}

bool Entity::getHighlighted() {
	return this->highlighted;
}
#pragma endregion

Entity::~Entity(void)
{
}
