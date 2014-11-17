#include "Spawnpoint.h"
#include "Rabbit.h"
#include "PlayState.h"
#include "NPCFactory.h"
#include "GameTimer.h"
#include <iostream>

Spawnpoint::Spawnpoint(int id, double x, double y, int chunkSize, string spawnType, int maxChildren, int walkRange) 
: Entity(id, x, y, chunkSize)
{
	init(spawnType, maxChildren, walkRange);
	
	this->spawnpointTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelPurple.png").c_str());
}

void Spawnpoint::init(string spawnType, int maxChildren, int walkRange)
{
	PlayState::Instance()->getMainEntityContainer()->getSpawnpointContainer()->add(this);
	this->curChildren = 0;
	this->maxChildren = maxChildren;
	this->spawnType = spawnType;
	this->spawnInterval = 90000; //1,5 minuten
	this->walkRange = walkRange;
	spawnMob();
}

void Spawnpoint::drawSpawnpointArea()
{
	Camera* c = PlayState::Instance()->getCamera();

	spawnpointRect.x = this->getX() - c->getX() - this->walkRange;
	spawnpointRect.y = this->getY() - c->getY() - this->walkRange;
	spawnpointRect.w = this->walkRange *2;
	spawnpointRect.h = this->walkRange *2;

	GameStateManager::Instance()->sdlInitializer->drawTexture(this->spawnpointTexture,&this->spawnpointRect,NULL);
}

void Spawnpoint::spawnMob()
{
	if (curChildren < maxChildren)
	{
		if (spawnType == "rabbit")
		{
			NPCFactory::Instance()->createRabbit(this);
		}
		if (spawnType == "wasp")
		{
			NPCFactory::Instance()->createWasp(this);
		}
		this->curChildren++;
		this->lastSpawnTime = GameTimer::Instance()->getGameTime();
	}
}

void Spawnpoint::decreaseChildren()
{
	this->curChildren--;
}

int Spawnpoint::getWalkRange()
{
	return this->walkRange;
}

void Spawnpoint::update()
{
	if(GameTimer::Instance()->getGameTime() > lastSpawnTime + spawnInterval)
	{
		spawnMob();
	}
}

Spawnpoint::~Spawnpoint()
{
	SDL_DestroyTexture(spawnpointTexture);
	spawnpointTexture = nullptr;
}
