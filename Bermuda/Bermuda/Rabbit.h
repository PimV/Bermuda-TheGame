#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Rabbit :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint);
	~Rabbit();
	void walk(double dt);
	void update(double dt);
private:
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool intersections(CollidableEntity* collidableEntity);

	long timeSinceLastAction;
};