#include "Rabbit.h"
#include "PlayState.h"
#include <time.h>
#include <random>

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
	#pragma endregion Moving_stuff

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
	#pragma endregion Animation_stuff
	
	#pragma region Interactable_stuff
	this->interactTime = 500;
	this->animationType = AnimationEnumType::Attackable;
	#pragma endregion Interactable_stuff

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->StopAnimation();
}


void Rabbit::update(double dt)
{
	if (this->getHealthPoints() > 1)
	{
		this->directionsAndMove(dt);
	}
	else
	{
		this->setDestroyedState();
	}
}

void Rabbit::directionsAndMove(double dt)
{
	random_device dev;
	default_random_engine dre(dev());

	uniform_int_distribution<int> dist1(500, 5000);
	int timeWait = dist1(dre);

	if (timeSinceLastAction < timeWait)
	{
		timeSinceLastAction += GameTimer::Instance()->getFrameTime();
	}
	else {
		timeSinceLastAction = 0;

		uniform_int_distribution<int> dist2(1, 8);
		int randomNumberMoveDirection = dist2(dre);

		this->StopAnimation();

		switch (randomNumberMoveDirection)
		{
		case 1:
			movingRight = true;
			movingLeft = false;
			break;
		case 2:
			movingRight = false;
			movingLeft = true;
			break;
		case 3:
			movingDown = true;
			movingUp = false;
			break;
		case 4:
			movingDown = false;
			movingUp = true;
			break;
		default:
			movingUp = false;
			movingDown = false;
			movingRight = false;
			movingLeft = false;
			dx = 0;
			dy = 0;
			break;
		}

		if ((getX() - getSpawnPoint()->getX()) > getSpawnPoint()->getWalkRange())
		{
			movingRight = false;
			movingLeft = true;
		}
		else if ((getSpawnPoint()->getX() - getX()) > getSpawnPoint()->getWalkRange())
		{
			movingRight = true;
			movingLeft = false;
		}

		if ((getY() - getSpawnPoint()->getY()) > getSpawnPoint()->getWalkRange())
		{
			movingDown = false;
			movingUp = true;
		}
		else if ((getSpawnPoint()->getY() - getY()) > getSpawnPoint()->getWalkRange())
		{
			movingDown = true;
			movingUp = false;
		}

	}
	this->move(dt);
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
	this->~Rabbit();
}

Rabbit::~Rabbit()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
