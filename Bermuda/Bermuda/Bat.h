#pragma once
#include "InteractableNPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Bat :
	public InteractableNPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
	private:
		// Replace methods to DrawableEntity & CollidableEntity
		void setImage(Image* image);
		void ResetDrawableEntityAndSetChunk();
		bool checkCollision(double newX, double newY);

	public:
		Bat(int id, Spawnpoint *spawnPoint, int firstImgID);

		void update(double dt);

		void interact(Player* player);
		void setDestroyedState();

		virtual ~Bat();
};
