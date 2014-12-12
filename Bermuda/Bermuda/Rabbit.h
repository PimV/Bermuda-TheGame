#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "Weapon.h"

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

	void interact(Player* player);
	void respawn();
	void setDestroyedState();

private:
	void directionsAndMove(double dt);
	
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();

	void removeFromContainers();
};
