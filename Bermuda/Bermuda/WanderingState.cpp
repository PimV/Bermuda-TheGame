#include "WanderingState.h"
#include "GameTimer.h"
#include <time.h>
#include <iostream>
#include <random>

WanderingState::WanderingState(Entity* entity)
{
	this->movableEntity = dynamic_cast<MovableEntity*>(entity);
	this->npc = dynamic_cast<NPC*>(entity);;
}


WanderingState::~WanderingState()
{
}


void WanderingState::update(double dt)
{
	std::random_device dev;
	std::default_random_engine dre(dev());

	std::uniform_int_distribution<int> dist1(500, 5000);
	int timeWait = dist1(dre);

	if (movableEntity->getTimeSinceLastAction() < timeWait)
	{
		movableEntity->setTimeSinceLastAction(movableEntity->getTimeSinceLastAction() + GameTimer::Instance()->getFrameTime());
	}
	else {
		movableEntity->setTimeSinceLastAction(0);

		std::uniform_int_distribution<int> dist2(1, 8);
		int randomNumberMoveDirection = dist2(dre);

		movableEntity->StopAnimation();

		switch (randomNumberMoveDirection)
		{
		case 1:
			movableEntity->movingRight = true;
			movableEntity->movingLeft = false;
			break;
		case 2:
			movableEntity->movingRight = false;
			movableEntity->movingLeft = true;
			break;
		case 3:
			movableEntity->movingDown = true;
			movableEntity->movingUp = false;
			break;
		case 4:
			movableEntity->movingDown = false;
			movableEntity->movingUp = true;
			break;
		default:
			movableEntity->movingUp = false;
			movableEntity->movingDown = false;
			movableEntity->movingRight = false;
			movableEntity->movingLeft = false;
			movableEntity->setDx(0);
			movableEntity->setDy(0);
			break;
		}

		if ((movableEntity->getX() - npc->getSpawnPoint()->getX()) > npc->getSpawnPoint()->getWalkRange())
		{
			movableEntity->movingRight = false;
			movableEntity->movingLeft = true;
		}
		else if ((npc->getSpawnPoint()->getX() - movableEntity->getX()) > npc->getSpawnPoint()->getWalkRange())
		{
			movableEntity->movingRight = true;
			movableEntity->movingLeft = false;
		}

		if ((movableEntity->getY() - npc->getSpawnPoint()->getY()) > npc->getSpawnPoint()->getWalkRange())
		{
			movableEntity->movingDown = false;
			movableEntity->movingUp = true;
		}
		else if ((npc->getSpawnPoint()->getY() - movableEntity->getY()) > npc->getSpawnPoint()->getWalkRange())
		{
			movableEntity->movingDown = true;
			movableEntity->movingUp = false;
		}

	}
	movableEntity->move(dt);
}