#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "IMovable.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Rabbit:
	public NPC,
	public Evasive,
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint, GameStateManager* gsm, MainEntityContainer* mec);
	~Rabbit();
private:
	int firstImgID;
};

	