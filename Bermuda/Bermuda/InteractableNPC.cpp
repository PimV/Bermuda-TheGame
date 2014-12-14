#include "InteractableNPC.h"
#include <time.h>
#include <iostream>
#include <random>


InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint):
NPC(id, 20, 1, 50, spawnPoint), 
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 0, 0, 0, 0),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->id = id;
	this->animationType = AnimationEnumType::Attackable;
}

#pragma region Getters
int InteractableNPC::getHeathPoints()
{
	return this->healthPoints;
}

int InteractableNPC::getAttackPoints()
{
	return this->attackPoints;
}

int InteractableNPC::getActionRange()
{
	return this->actionRange;
}

Spawnpoint* InteractableNPC::getSpawnPoint()
{
	return this->spawnPoint;
}
#pragma endregion

#pragma region Setters
void InteractableNPC::setHealthPoints(int healthPoints)
{
	this->healthPoints = healthPoints;
}

void InteractableNPC::setAttackPoints(int attackPoints)
{
	this->attackPoints = attackPoints;
}

void InteractableNPC::setActionRange(int actionRange)
{
	this->actionRange = actionRange;
}

void InteractableNPC::setSpawnPoint(Spawnpoint *spawnPoint)
{
	this->spawnPoint = spawnPoint;
}
#pragma endregion

void InteractableNPC::interact(Player* player)
{

}

void InteractableNPC::update(double dt)
{
	if (this->getHeathPoints() > 1)
	{
		this->directionsAndMove(dt);
	}
	else
	{
		this->setDestroyedState();
	}
}


void InteractableNPC::directionsAndMove(double dt)
{
	std::random_device dev;
	std::default_random_engine dre(dev());

	std::uniform_int_distribution<int> dist1(500, 5000);
	int timeWait = dist1(dre);

	if (timeSinceLastAction < timeWait)
	{
		timeSinceLastAction += GameTimer::Instance()->getFrameTime();
	}
	else {
		timeSinceLastAction = 0;

		std::uniform_int_distribution<int> dist2(1, 8);
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
InteractableNPC::~InteractableNPC(void)
{
}
