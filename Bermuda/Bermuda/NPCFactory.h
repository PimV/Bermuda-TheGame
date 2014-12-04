#pragma once
#include "SpawnPoint.h"
#include "ImageLoader.h"
#include "header_loader.h"
#include <map>


class NPCFactory
{
private:
	static NPCFactory npcFactory;

	std::map<std::string, int> FirstImageIDs;

public:
	NPCFactory();
	void loadNPCTileSets(ImageLoader* imgLoader);
	void createRabbit(Spawnpoint* sp);
	void createWasp(Spawnpoint* sp);
	void createBat(Spawnpoint* sp);
	void createWolf(Spawnpoint* sp);

	~NPCFactory();
	static NPCFactory* Instance() {
		return &npcFactory;
	};
};

