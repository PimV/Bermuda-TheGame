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
	bool checkCollision(double newX, double newY);
private:
	void directionsAndMove(double dt);
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
};

