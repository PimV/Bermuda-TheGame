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

	SDL_Texture* spawnpointTexture;
	SDL_Rect spawnpointRect;

	//methodes
	void init(std::string spawnType, int maxChildren, int walkRange);
	void spawnMob();

public:
	Spawnpoint(int id, double x, double y, std::string spawnType, int maxChildren, int walkRange);

	void decreaseChildren();
	int getWalkRange();
	void update();
	void drawSpawnpointArea();

	virtual ~Spawnpoint();
};
