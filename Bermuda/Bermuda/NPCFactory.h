#pragma once
#include "SpawnPoint.h"
#include "ImageLoader.h"
#include "Image.h"
#include "header_loader.h"
#include <map>


class NPCFactory
{
private:
	static NPCFactory npcFactory;

	std::map<std::string, Image*> NPCImages;

public:
	NPCFactory();
	void loadNPCTileSets(ImageLoader* imgLoader);
	void createRabbit(Spawnpoint* sp);
	void createWasp(Spawnpoint* sp);

	~NPCFactory();
	static NPCFactory* Instance() {
		return &npcFactory;
	};
};

