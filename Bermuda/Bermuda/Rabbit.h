#pragma once
#include "NPC.h"
#include "Evasive.h"

class Rabbit : 
	public NPC,
	public Evasive
{
public:
	Rabbit(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint);
	~Rabbit();
};

