#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Wasp :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Wasp(int id, int chunkSize, Spawnpoint *spawnPoint);
	~Wasp();
	void walk(double dt);
	void update(double dt);
private:
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool intersections(CollidableEntity* collidableEntity);
};

