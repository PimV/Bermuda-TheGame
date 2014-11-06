#pragma once
#include "header_loader.h"
#include "Entity.h"

class Spawnpoint :
	public virtual Entity
{
private:
	//variables
	int curChildren;
	int maxChildren;
	std::string spawnType;
	int lastSpawnTime;
	int spawnInterval;
	int walkRange;

	//methodes
	void init(std::string spawnType, int maxChildren, int walkRange);
	void spawnMob();

public:

	void decreaseChildren();
	int getWalkRange();
	void update();

	//Constructor destructor
	Spawnpoint(int id, double x, double y, int chunkSize, std::string spawnType, int maxChildren, int walkRange);
	virtual ~Spawnpoint();
};

