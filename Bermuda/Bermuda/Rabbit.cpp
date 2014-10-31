#include "Rabbit.h"

Rabbit::Rabbit(int id, int chunkSize, Spawnpoint* spawnPoint, GameStateManager* gsm, MainEntityContainer* mec) :
	NPC(id, chunkSize, 5, 1, 20, 5, spawnPoint),
	Entity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize),
	DrawableEntity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize, nullptr),
	CollidableEntity(id, this->getSpawnPoint()->getX(), this->getSpawnPoint()->getY(), chunkSize),
	IMovable(moveSpeed)
{
	this->setCollisionHeight(this->getHeight() - 15);
	this->setCollisionWidth(this->getWidth() / 4);
	this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
	this->setCollisionY(0);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->stopSpeed = 0.8;
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

Rabbit::~Rabbit()
{

}