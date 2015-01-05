#include "Wolf.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "AggressiveBehaviour.h"

Wolf::Wolf(int id, Spawnpoint* spawnPoint, int firstImgID) :
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	InteractableNPC(id, 40, 3, 150, 10, spawnPoint, -12, -15, 68, 78, 500),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 13, 20, 23, 24),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(48);
	this->setHeight(48);

	#pragma region Moving_stuff
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	#pragma endregion

	#pragma region Animation_stuff
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 3; 
	this->animationWalkLeftRow = 1;
	this->animationWalkDownRow = 0, 
	this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; 
	this->animationWalkStartColumn = 0;
	this->animationWalkEndColumn = 3;
	this->frameAmountX = 4, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;
	#pragma endregion

	#pragma region Interactable_stuff
	this->interactTime = 500;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;
	#pragma endregion

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new AggressiveBehaviour( new StateMachine<Entity>(this) );
}

void Wolf::update(double dt)
{
	if (this->getHealthPoints() > 0)
	{
		this->behaviour->update(dt);
	}
	else
	{
		this->setDestroyedState();
	}
}

void Wolf::interact(Player* player)
{
	if (player->getInventory()->getSelectedItem()->hasItemType(ItemType::Weapon))
	{
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);

		if (this->trackInteractTimes())
		{
			player->setCorrectToolSelected(false);
			this->currentInteractTime = 0;
			this->setHealthPoints( this->getHealthPoints() - dynamic_cast<class Weapon*>(player->getInventory()->getSelectedItem())->getAttackDamage() );
		}
	}
	else
	{
		player->setCorrectToolSelected(false);
	}
}

void Wolf::setDestroyedState() 
{
	// TODO: add Wolf killed to status tracker
	this->getSpawnPoint()->decreaseChildren();
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

void Wolf::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Wolf::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

bool Wolf::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Wolf::~Wolf()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
