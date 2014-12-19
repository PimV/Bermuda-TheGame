#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Scorpion :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Scorpion(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Scorpion();

	void update(double dt);
	void changeState(State* pNewState);
private:
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};

