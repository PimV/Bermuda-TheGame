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
	if (this->getEnabled())
	{
		Camera* c = PlayState::Instance()->getCamera();

		collidableRect.x = this->getX() - c->getX() + this->getCollisionX();
		collidableRect.y = this->getY() - c->getY() + this->getCollisionY();
		collidableRect.w = this->getCollisionWidth();
		collidableRect.h = this->getCollisionHeight();

		GameStateManager::Instance()->sdlInitializer->drawTexture(this->collidableTexture, &this->collidableRect, NULL);
	}
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

bool CollidableEntity::checkCollision(double x, double y) {
	//Calculate begin and end chunks for the collision check (+1 and -1 to make it a little bigger then the current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			std::vector<CollidableEntity*>* vec = PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (CollidableEntity* e : *vec)
				{
					if (this->intersects(x, y, e))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CollidableEntity::checkCollision() 
{
	return this->checkCollision(this->getX(), this->getY());
}

bool CollidableEntity::intersects(double x, double y, CollidableEntity* collidableEntity) {
	if(this == collidableEntity)
	{
		return false;
	}

	double targetLeft = collidableEntity->getX() + collidableEntity->getCollisionX();
	double targetRight = collidableEntity->getX() + collidableEntity->getCollisionX() + collidableEntity->getCollisionWidth();
	double targetTop = collidableEntity->getY() + collidableEntity->getCollisionY();
	double targetBot = collidableEntity->getY() + collidableEntity->getCollisionY() + collidableEntity->getCollisionHeight();

	double thisLeft = x + this->getCollisionX();
	double thisRight = x + this->getCollisionX() + this->getCollisionWidth();
	double thisTop = y + this->getCollisionY();
	double thisBot = y + this->getCollisionY() + this->getCollisionHeight();

	if (this->getEnabled() &&
		thisLeft < targetRight &&
		thisRight > targetLeft &&
		thisTop < targetBot &&
		thisBot > targetTop)
	{
		return true;
	}

	return false;
}

bool CollidableEntity::intersects(CollidableEntity* collidableEntity)
{
	return this->intersects(this->getX(), this->getY(), collidableEntity);
}

CollidableEntity::~CollidableEntity()
{
	SDL_DestroyTexture(collidableTexture);
}
