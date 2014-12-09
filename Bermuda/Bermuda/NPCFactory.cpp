#include "NPCFactory.h"
#include "Rabbit.h"
#include "Wasp.h"
#include "Bat.h"
#include "Wolf.h"
#include "PlayState.h"
#include "GameStateManager.h"

NPCFactory NPCFactory::npcFactory;

NPCFactory::NPCFactory()
{
}

void NPCFactory::loadNPCTileSets(ImageLoader* imgLoader)
{
	FirstImageIDs["rabbit"] = imgLoader->loadTileset("NPC\\rabbit.png", 36, 36);
	FirstImageIDs["wasp"] = imgLoader->loadTileset("NPC\\wasp.png", 32, 32);
	FirstImageIDs["bat"] = imgLoader->loadTileset("NPC\\bat.png", 32, 32);
	FirstImageIDs["wolf"] = imgLoader->loadTileset("NPC\\wolf.png", 48, 48);
}

void NPCFactory::createRabbit(Spawnpoint* sp)
{
	new Rabbit(1001, sp, FirstImageIDs["rabbit"]);
}

void NPCFactory::createWasp(Spawnpoint* sp)
{
	new Wasp(2001, sp, FirstImageIDs["wasp"]);
}

void NPCFactory::createBat(Spawnpoint* sp)
{
	new Bat(2001, sp, FirstImageIDs["bat"]);
}

void NPCFactory::createWolf(Spawnpoint* sp)
{
	new Wolf(2001, sp, FirstImageIDs["wolf"]);
}

NPCFactory::~NPCFactory()
{
}
