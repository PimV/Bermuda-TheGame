#include "NPCFactory.h"
#include "Rabbit.h"
#include "Wasp.h"
#include "PlayState.h"
#include "GameStateManager.h"

NPCFactory NPCFactory::npcFactory;

NPCFactory::NPCFactory()
{
}

void NPCFactory::loadNPCTileSets(ImageLoader* imgLoader)
{
	NPCImages["rabbit"] = imgLoader->getMapImage(imgLoader->loadTileset("rabbitsheet.png", 36, 36));
	NPCImages["wasp"] = imgLoader->getMapImage(imgLoader->loadTileset("bee.png", 32, 32));
}

void NPCFactory::createRabbit(Spawnpoint* sp)
{
	//TODO: 300 chunksize ombouwen. (MapLoader singleton maken?)
	new Rabbit(1001, 300, sp, GameStateManager::Instance(), PlayState::Instance()->getMainEntityContainer());
}

void NPCFactory::createWasp(Spawnpoint* sp)
{
	//TODO: 300 chunksize ombouwen. (MapLoader singleton maken?)
	new Wasp(2001, 300, sp, GameStateManager::Instance(), PlayState::Instance()->getMainEntityContainer());
}


NPCFactory::~NPCFactory()
{
}
