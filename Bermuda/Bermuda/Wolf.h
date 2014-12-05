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
	~Wolf();
	void update(double dt);
private:
	void directionsAndMove(double dt);


	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};

