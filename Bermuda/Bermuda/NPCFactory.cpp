#include "NPCFactory.h"
#include "Rabbit.h"
#include "Wasp.h"
#include "Bat.h"
#include "PlayState.h"
#include "GameStateManager.h"

NPCFactory NPCFactory::npcFactory;

NPCFactory::NPCFactory()
{
}

void NPCFactory::loadNPCTileSets(ImageLoader* imgLoader)
{
	FirstImageIDs["rabbit"] = imgLoader->loadTileset("rabbitsheet.png", 36, 36);
	FirstImageIDs["wasp"] = imgLoader->loadTileset("wasp.png", 32, 32);
	FirstImageIDs["bat"] = imgLoader->loadTileset("bat.png", 32, 32);
}

void NPCFactory::createRabbit(Spawnpoint* sp)
{
	//TODO: 300 chunksize ombouwen. (MapLoader singleton maken?)
	new Rabbit(1001, sp, FirstImageIDs["rabbit"]);
}

void NPCFactory::createWasp(Spawnpoint* sp)
{
	//TODO: 300 chunksize ombouwen. (MapLoader singleton maken?)
	new Wasp(2001, sp, FirstImageIDs["wasp"]);
}

void NPCFactory::createBat(Spawnpoint* sp)
{
	//TODO: 300 chunksize ombouwen. (MapLoader singleton maken?)
	new Bat(2001, sp, FirstImageIDs["bat"]);
}


NPCFactory::~NPCFactory()
{
}
