#pragma once
#include "Entity.h"

class Spawnpoint :
	public Entity
{
private:
	int curChilderen;
	int maxChilderen;
	enum type;
	int id;

	void SpawnMob();
public:
	void Check();

	Spawnpoint(int id); // --> Spawnpoint(int type)
	Spawnpoint(int id, double x, double y, int chunkSize);
	virtual ~Spawnpoint();
};

