#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Rabbit :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Rabbit(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Rabbit();

	void update(double dt);
private:
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};
