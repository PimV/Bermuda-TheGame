#include "AggressiveState.h"
#include "MovableEntity.h"
#include "NPC.h"
#include "PlayState.h"
#include <random>
#include <assert.h>

AggressiveState::AggressiveState(void)
{
}

AggressiveState* AggressiveState::Instance()
{
	static AggressiveState instance;
	return &instance;
}

void AggressiveState::enter(Entity* entity)
{
	this->entity = entity;
	this->attackRange = dynamic_cast<NPC*>(entity)->getActionRange();
	this->actionRange = dynamic_cast<NPC*>(entity)->getAttackRange();
}

void AggressiveState::exit(Entity* entity)
{
	this->actionRange = 0;
	this->attackRange = 0;
	this->entity = nullptr;
}

void AggressiveState::execute(Entity* entity, double dt)
{
	assert(entity && dt && " execute AgrassiveState");

	MovableEntity* movableEntity = dynamic_cast<MovableEntity*>(this->entity);
	NPC* npc = dynamic_cast<NPC*>(this->entity);

	movableEntity->movingLeft = false;
	movableEntity->movingRight = false;
	movableEntity->movingUp = false;
	movableEntity->movingDown = false;

	double playerCenterX = PlayState::Instance()->getPlayer()->getCenterX();
	double playerCenterY = PlayState::Instance()->getPlayer()->getCenterY();

	double offsetX = playerCenterX - movableEntity->getCenterX();
	double offsetY = playerCenterY - movableEntity->getCenterY();
	double offsetTotal = fabs(offsetX) + fabs(offsetY);

	double xDir = (offsetX / offsetTotal);
	double yDir = (offsetY / offsetTotal);

	if (xDir >= -1 && xDir <= -0.33)
	{
		movableEntity->movingLeft = true;
	}
	if (xDir >= 0.33 && xDir <= 1)
	{
		movableEntity->movingRight = true;
	}
	if (yDir >= -1 && yDir <= -0.33)
	{
		movableEntity->movingUp = true;
	}
	if (yDir >= 0.33 && yDir <= 1)
	{
		movableEntity->movingDown = true;
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
			if (playerCenterX < movableEntity->getCenterX())
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
			if (playerCenterY < movableEntity->getCenterY())
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

AggressiveState::~AggressiveState(void)
{

}
