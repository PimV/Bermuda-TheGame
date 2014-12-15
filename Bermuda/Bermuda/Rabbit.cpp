#include "Rabbit.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "Weapon.h"

Rabbit::Rabbit(int id, Spawnpoint* spawnPoint, int firstImgID) :
NPC(id, 5, 1, 50, spawnPoint),
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 4, 20, 28, 12),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY()),
InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), -20, -20, 75, 75),
HealthEntity(id,spawnPoint->getX(), spawnPoint->getY(), 50)
{
	this->setWidth(36);
	this->setHeight(36);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	//this->interaction = false;

	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1, this->animationWalkLeftRow = 3;
	this->animationWalkDownRow = 0, this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 7;

	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 8, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->StopAnimation();

	this->interactTime = 200;
	this->animationType = AnimationEnumType::AttackSpear;
}

void Rabbit::update(double dt) {

	if(this->getShowBar() == true)
	{
		if(this->getTimeStartShowBar() + 2000 < GameTimer::Instance()->getGameTime())
		{
			this->setShowBar(false);
		}
	}

	this->directionsAndMove(dt);
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

void Rabbit::draw(Camera* camera, SDL_Renderer* renderer)
{
	DrawableEntity::draw(camera, renderer);
		
	if(this->getShowBar())
	{
		double barWidth = 50;
		double maxPercentage = 100;
		this->greyRect.x = this->getX() - PlayState::Instance()->getCamera()->getX() - ((barWidth - this->getWidth()) / 2);
		this->greyRect.y = this->getY() - PlayState::Instance()->getCamera()->getY() - 20;
		this->greyRect.w = barWidth;
		this->greyRect.h = 6;

		this->redRect.x = this->getX() - PlayState::Instance()->getCamera()->getX() - ((barWidth - this->getWidth()) / 2);
		this->redRect.y = this->getY() - PlayState::Instance()->getCamera()->getY() - 20;
		this->redRect.w = (barWidth / maxPercentage) * this->getPercentageOfCurrentHealth();
		this->redRect.h = 6;

		GameStateManager::Instance()->sdlInitializer->drawTexture(this->greyText,&this->greyRect,NULL);
		GameStateManager::Instance()->sdlInitializer->drawTexture(this->redText,&this->redRect,NULL);
	}
}

//Interact methods
void Rabbit::interact(Player* player)
{
	//Currently only checken spear instead of any weapon
	if(player->getInventory()->spearSelected())
	{
		this->setTimeStartShowBar(GameTimer::Instance()->getGameTime());
		this->setShowBar(true);

		player->setCorrectToolSelected(true);
		if (this->trackInteractTimes()) 
		{
			this->decreaseHealth(5);
			this->currentInteractTime = 0;

			if(this->getHealth() == 0)
			{
				PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
			}
		}
	}
}

void Rabbit::setDestroyedState()
{

}

Rabbit::~Rabbit()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}