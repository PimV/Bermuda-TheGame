#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Wolf :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Wolf(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Wolf();

	void update(double dt);
	void changeState(State<Entity>* pNewState);
private:
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};

