#pragma once
#include "InteractableNPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "AttackingNPC.h"

class Wolf :
	public InteractableNPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity,
	public AttackingNPC
{
	private:
		void setImage(Image* image);
		void ResetDrawableEntityAndSetChunk();
		bool checkCollision(double newX, double newY);

	protected:
		//

	public:
		Wolf(int id, Spawnpoint *spawnPoint, int firstImgID);
		virtual ~Wolf();

		void update(double dt);
		void attack();
};
