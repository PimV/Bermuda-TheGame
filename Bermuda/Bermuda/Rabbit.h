#pragma once
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "InteractableNPC.h"
#include "Weapon.h"

class Rabbit :
	public InteractableNPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
	private:
		// Replace methods to DrawableEntity & CollidableEntity
		void setImage(Image* image);
		void ResetDrawableEntityAndSetChunk();

	protected:
		//

	public:
		Rabbit(int id, Spawnpoint *spawnPoint, int firstImgID);
		virtual ~Rabbit();

		void update(double dt);
		bool checkCollision(double newX, double newY);

		void interact(Player* player);
		void setDestroyedState();
};
