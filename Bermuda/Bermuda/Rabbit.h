#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "IMovable.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Rabbit : 
	public NPC,
	public Evasive,
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Rabbit(int id, int chunkSize, int healthPoints, int attackPoints, int moveSpeed, int walkRange, int actionRange, Spawnpoint *spawnPoint);
	~Rabbit();
};

