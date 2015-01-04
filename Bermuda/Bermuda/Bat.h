#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "AttackingNPC.h"

class Bat :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity,
	public AttackingNPC
{
	private:
		// Replace methods to DrawableEntity & CollidableEntity
		void setImage(Image* image);
		void ResetDrawableEntityAndSetChunk();
		bool checkCollision(double newX, double newY);

	protected:
		//

	public:
		Bat(int id, Spawnpoint *spawnPoint, int firstImgID);

		void update(double dt);
		void attack();

		virtual ~Bat();
};
