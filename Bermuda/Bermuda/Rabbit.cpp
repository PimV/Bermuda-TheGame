#include "Rabbit.h"
#include "PlayState.h"
#include <time.h>
#include <random>
#include "WanderAround.h"

Rabbit::Rabbit(int id, Spawnpoint* spawnPoint, int firstImgID) :
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
InteractableNPC(id, 20, 0, 1, spawnPoint, -12, -15, 68, 78),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 4, 20, 28, 12),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(36);
	this->setHeight(36);
	this->setSpawnPoint( spawnPoint );

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

	this->healthPoints = 20;
	this->attackPoints = 0;
	this->actionRange = 1;

	#pragma region Animation_stuff
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1, this->animationWalkLeftRow = 3;
	this->animationWalkDownRow = 0, this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 7;

	this->frameAmountX = 8, this->frameAmountY = 4, this->CurrentFrame = 0;
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

	this->m_pStateMachine = new StateMachine<Entity>(this);
	this->m_pStateMachine->setCurrentState(WanderAround::Instance());
}

void Rabbit::update(double dt)
{
	if (this->getHealthPoints() > 0)
	{
		this->m_pStateMachine->update(dt);
	}
	else
	{
		this->setDestroyedState();
	}
}


void Rabbit::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Rabbit::ResetDrawableEntityAndSetChunk()
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

bool Rabbit::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

void Rabbit::interact(Player* player)
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

void Rabbit::setDestroyedState() 
{
	// TODO: add rabbit killed to status tracker
	this->getSpawnPoint()->decreaseChildren();
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

Rabbit::~Rabbit()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
