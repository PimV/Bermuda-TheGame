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
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint, int firstImgID);
	~Rabbit();
	void update(double dt);
private:
	void directionsAndMove(double dt);


	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkIntersects(CollidableEntity* collidableEntity);
};
