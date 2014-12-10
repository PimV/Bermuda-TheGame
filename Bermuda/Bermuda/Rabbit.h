#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Rabbit :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Rabbit(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Rabbit();

	void update(double dt);
	bool checkCollision(double newX, double newY);
private:
	void directionsAndMove(double dt);
	
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
};
