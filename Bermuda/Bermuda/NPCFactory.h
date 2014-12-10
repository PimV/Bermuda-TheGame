#pragma once
#include "SpawnPoint.h"
#include "ImageLoader.h"
#include "header_loader.h"
#include "NPCType.h"
#include <map>


class NPCFactory
{
private:
	static NPCFactory npcFactory;

	std::map<NPCType, int> FirstImageIDs;

public:
	NPCFactory();
	void loadNPCTileSets(ImageLoader* imgLoader);

	bool createNPC(NPCType type, Spawnpoint* sp);

	~NPCFactory();
	static NPCFactory* Instance() {
		return &npcFactory;
	};
};

