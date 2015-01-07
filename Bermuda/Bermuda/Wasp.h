#pragma once
#include "InteractableNPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "Weapon.h"

class Wasp :
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
		Wasp(int id, Spawnpoint *spawnPoint, int firstImgID);
		virtual ~Wasp();

		void update(double dt);
		
		void interact(Player* player);
		void setDestroyedState();
};
