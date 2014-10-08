#include "NPC.h"
#include "Spawnpoint.h"
#include <time.h>
#include <iostream>

NPC::NPC(int id, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint) : Entity(id)
{
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->walkRange = walkRange;
	this->actionRange = actionRange;
	this->spawnPoint = spawnPoint;
	this->walking = false;
}

void NPC::walk()
{
	if (walking == false) {
		walking = true;

		srand(time(NULL));

		int distanceX = rand() % (walkRange * 2) + (walkRange * -1);
		int distanceY = rand() % (walkRange * 2) + (walkRange * -1);

		int destinationX = this->spawnPoint->getX() + distanceX;
		int destinationY = this->spawnPoint->getY() + distanceY;

		// moveTo(destinationX, destinationY);

		walking = false;
	}
}

NPC::~NPC(void)
{
}
