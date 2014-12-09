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

bool NPCFactory::createNPC(NPCType type, Spawnpoint* sp)
{
	NPC* npc = nullptr;

	switch((int)type)
	{
	case (int)NPCType::Rabbit:
		npc = new Rabbit(1001, sp, FirstImageIDs["rabbit"]);
		break;
	case (int)NPCType::Wolf:
		npc = new Wolf(2001, sp, FirstImageIDs["wolf"]);
		break;
	case (int)NPCType::Wasp:
		npc = new Wasp(2001, sp, FirstImageIDs["wasp"]);
		break;
	case (int)NPCType::Bat:
		npc = new Bat(2001, sp, FirstImageIDs["bat"]);
		break;
	case (int)NPCType::Scorpion:
		//scorpion code
		break;
	}

	//If the new NPC detects collision -> delete it and return false
	if(npc != nullptr && dynamic_cast<CollidableEntity*>(npc)->checkCollision())
	{
		std::cout << "NEW NPC COLLISION" << std::endl;
		delete npc;
		return false;
	}

	return true;
}

NPCFactory::~NPCFactory()
{
}
