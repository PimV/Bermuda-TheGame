#include "Bat.h"
#include "PlayState.h"
#include <random>
#include "EvasiveBehaviour.h"

Bat::Bat(int id, Spawnpoint* spawnPoint, int firstImgID) :
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
InteractableNPC(id, 25, 1, 150, 30, spawnPoint, -18, -20, 68, 78, 500),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 8, 20, 16, 12),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(32);
	this->setHeight(32);

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
	this->keepAnimationWhenIdle = true;
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 0, this->animationWalkLeftRow = 1;
	this->animationWalkDownRow = 2, this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 0, this->animationWalkEndColumn = 3;
	this->frameAmountX = 4, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;
	#pragma endregion

	#pragma region Interactable_stuff
	this->interactTime = 600;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;
	#pragma endregion

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new EvasiveBehaviour( new StateMachine<Entity>(this) );
}

void Bat::update(double dt)
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

void Bat::interact(Player* player)
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

void Bat::setDestroyedState() 
{
	PlayState::Instance()->getPlayer()->getStatusTracker()->addAchievementCount(AchievementsEnum::BATSKILLED);
	this->getSpawnPoint()->decreaseChildren();
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

void Bat::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Bat::ResetDrawableEntityAndSetChunk()
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

bool Bat::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Bat::~Bat()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
