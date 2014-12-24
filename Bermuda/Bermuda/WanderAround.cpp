#include "WanderAround.h"
#include "MovableEntity.h"
#include "NPC.h"
#include "GameTimer.h"
#include <time.h>
#include <iostream>
#include <random>
#include <assert.h>

WanderAround* WanderAround::Instance()
{
	static WanderAround instance;
	return &instance;
}

void WanderAround::enter(Entity* entity)
{

}

void WanderAround::exit(Entity* entity)
{

}

void WanderAround::execute(Entity* entity, double dt)
{
	assert(entity && dt);

	MovableEntity* movableEntity = dynamic_cast<MovableEntity*>(entity);
	NPC* npc = dynamic_cast<NPC*>(entity);

	std::random_device dev;
	std::default_random_engine dre(dev());

	std::uniform_int_distribution<int> dist1(500, 5000);
	std::uniform_int_distribution<int> dist2(0, 1);
	int timeWait = dist1(dre);

	if (movableEntity->getTimeSinceLastAction() < timeWait)
	{
		movableEntity->setTimeSinceLastAction(static_cast<long>(movableEntity->getTimeSinceLastAction() + GameTimer::Instance()->getFrameTime()));
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

	//Move and avoid collision
	if (movableEntity->canMove(dt))
	{
		movableEntity->move(dt);
	}
	else
	{
		if (movableEntity->movingUp && movableEntity->movingRight)
		{
			movableEntity->movingUp = false;
			if (movableEntity->canMove(dt))
			{
				movableEntity->move(dt);
			}
			else
			{
				movableEntity->movingUp = true;
				movableEntity->movingRight = false;
				movableEntity->move(dt);
			}
		}
		else if (movableEntity->movingRight && movableEntity->movingDown)
		{
			movableEntity->movingRight = false;
			if (movableEntity->canMove(dt))
			{
				movableEntity->move(dt);
			}
			else
			{
				movableEntity->movingRight = true;
				movableEntity->movingDown = false;
				movableEntity->move(dt);
			}
		}
		else if (movableEntity->movingDown && movableEntity->movingLeft)
		{
			movableEntity->movingDown = false;
			if (movableEntity->canMove(dt))
			{
				movableEntity->move(dt);
			}
			else
			{
				movableEntity->movingDown = true;
				movableEntity->movingLeft = false;
				movableEntity->move(dt);
			}
		}
		else if (movableEntity->movingLeft && movableEntity->movingUp)
		{
			movableEntity->movingLeft = false;
			if (movableEntity->canMove(dt))
			{
				movableEntity->move(dt);
			}
			else
			{
				movableEntity->movingLeft = true;
				movableEntity->movingUp = false;
				movableEntity->move(dt);
			}
		}
		else if (movableEntity->movingUp || movableEntity->movingDown)
		{
			int random = dist2(dre);

			if (random == 1)
			{
				movableEntity->movingUp = false;
				movableEntity->movingDown = false;
				movableEntity->movingRight = true;
			}
			else
			{
				movableEntity->movingUp = false;
				movableEntity->movingDown = false;
				movableEntity->movingLeft = true;
			}
			movableEntity->move(dt);
		}
		else if (movableEntity->movingLeft || movableEntity->movingRight)
		{
			int random = dist2(dre);

			if (random == 1)
			{
				movableEntity->movingLeft = false;
				movableEntity->movingRight = false;
				movableEntity->movingDown = true;
			}
			else
			{
				movableEntity->movingLeft = false;
				movableEntity->movingRight = false;
				movableEntity->movingUp = true;
			}
			movableEntity->move(dt);
		}
	}
}
