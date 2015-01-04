#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "AttackingNPC.h"

class Wasp :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity,
	public AttackingNPC
{
public:
	Wasp(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Wasp();

	void update(double dt);
	void attack();
private:
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);

};
