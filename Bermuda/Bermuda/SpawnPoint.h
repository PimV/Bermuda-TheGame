#pragma once
#include "Entity.h"

class Spawnpoint :
	public virtual Entity
{
private:
	//variables
	int curChilderen;
	int maxChilderen;
	enum spawnType;
	int type;

	//methodes
	void init();
	void spawnMob();

public:

	//Constructor destructor
	Spawnpoint(int type, double x, double y, int chunkSize);
	virtual ~Spawnpoint();
};

