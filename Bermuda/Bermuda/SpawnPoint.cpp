#include "Spawnpoint.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "NPCFactory.h"
#include "GameTimer.h"
#include "NPCType.h"

Spawnpoint::Spawnpoint(int id, double x, double y, string spawnType, int maxChildren, int walkRange) 
: Entity(id, x, y)
{
	init(spawnType, maxChildren, walkRange);
	
	//TODO: pixel word voor elke spawnpoint opnieuw ingeladen.
	this->spawnpointTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelPurple.png").c_str());
}

void Spawnpoint::init(string spawnType, int maxChildren, int walkRange)
{
	PlayState::Instance()->getMainEntityContainer()->getSpawnpointContainer()->add(this);
	this->curChildren = 0;
	this->maxChildren = maxChildren;
	this->spawnType = spawnType;

	this->spawnInterval = 90000;

	this->walkRange = walkRange;
	this->lastSpawnTime = 0;
	this->lastReSpawnTime = 0;
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
		bool npcSpawned = false;
		if (spawnType == "rabbit")
		{
			npcSpawned = NPCFactory::Instance()->createNPC(NPCType::Rabbit, this);
		}
		else if (spawnType == "wasp")
		{
			npcSpawned = NPCFactory::Instance()->createNPC(NPCType::Wasp, this);
		}
		else if (spawnType == "bat")
		{
			npcSpawned = NPCFactory::Instance()->createNPC(NPCType::Bat, this);
		}
		else if (spawnType == "wolf")
		{
			npcSpawned = NPCFactory::Instance()->createNPC(NPCType::Wolf, this);
		}		
		else if (spawnType == "scorpion")
		{
			npcSpawned = NPCFactory::Instance()->createNPC(NPCType::Scorpion, this);
		}

		if(npcSpawned)
		{
			++this->curChildren;
		}

	}
}

void Spawnpoint::decreaseChildren()
{
	if (this->curChildren > 0)
	{
		--this->curChildren;
	}
}

int Spawnpoint::getWalkRange()
{
	return this->walkRange;
}

void Spawnpoint::update()
{
	// cheack for a new spawn
	if(GameTimer::Instance()->getGameTime() > this->lastSpawnTime + this->spawnInterval)
	{
		this->spawnMob();
		this->increateSpawnTimer();
	}

	// chack for a respawn
	if(GameTimer::Instance()->getGameTime() > this->lastReSpawnTime + this->spawnInterval)
	{
		this->spawnMob();
		this->increateReSpawnTimer();
	}
}

void Spawnpoint::increateSpawnTimer()
{
	this->lastSpawnTime = GameTimer::Instance()->getGameTime();
}

void Spawnpoint::increateReSpawnTimer()
{
	this->lastReSpawnTime= GameTimer::Instance()->getGameTime();
}

Spawnpoint::~Spawnpoint()
{
	SDL_DestroyTexture(spawnpointTexture);
}
