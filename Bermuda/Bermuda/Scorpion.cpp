#include "Scorpion.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "AggressiveBehaviour.h"

Scorpion::Scorpion(int id, Spawnpoint* spawnPoint, int firstImgID) :
	InteractableNPC(id, 50, 2, 150, 35, spawnPoint, -18, -15, 68, 78, 500),
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 2, 8, 28, 21),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(48);
	this->setHeight(48);

	#pragma region Moving_stuff
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	#pragma endregion

	#pragma region Animation_stuff
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1; 
	this->animationWalkLeftRow = 2;
	this->animationWalkDownRow = 0, 
	this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; 
	this->animationWalkStartColumn = 0;
	this->animationWalkEndColumn = 3;
	this->frameAmountX = 6, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;

	this->StopAnimation();
	#pragma endregion

	#pragma region Interactable_stuff
	this->interactTime = 900;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;
	#pragma endregion

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->behaviour = new AggressiveBehaviour( new StateMachine<Entity>(this) );
}

void Scorpion::update(double dt)
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

void Scorpion::interact(Player* player)
{
	if (player->getInventory()->getWeaponSelected())
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

void Scorpion::setDestroyedState() 
{
	PlayState::Instance()->getPlayer()->getStatusTracker()->addAchievementCount(AchievementsEnum::SCORPIONSKILLED);
	PlayState::Instance()->getPlayer()->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Meat));
	this->getSpawnPoint()->decreaseChildren();
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

void Scorpion::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Scorpion::ResetDrawableEntityAndSetChunk()
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

bool Scorpion::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Scorpion::~Scorpion()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
