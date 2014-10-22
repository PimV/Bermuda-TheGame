#include "NPC.h"
#include "Spawnpoint.h"
#include <time.h>
#include <iostream>

NPC::NPC(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint) 
	: spawnPoint(spawnPoint), Entity(id,spawnPoint->getX(),spawnPoint->getY(),chunkSize)
{
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->walkRange = walkRange;
	this->actionRange = actionRange;
	this->walking = false;
}

void NPC::walk()
{
	// add timer
	// walking in Entity?

	if (walking == false) {
		walking = true;

		srand(time(NULL));

		double distanceX = rand() % (walkRange * 2) + (walkRange * -1);
		double distanceY = rand() % (walkRange * 2) + (walkRange * -1);

		double destinationX = this->spawnPoint->getX() + distanceX;
		double destinationY = this->spawnPoint->getY() + distanceY;

		// moveTo(destinationX, destinationY);

		walking = false;
	}
}

NPC::~NPC(void)
{
}
