#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Wasp :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Wasp(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Wasp();

	void update(double dt);
	void changeState(State<Entity>* pNewState);
private:
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};

