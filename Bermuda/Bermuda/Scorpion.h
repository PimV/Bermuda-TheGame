#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "AttackingNPC.h"

class Scorpion :
	public NPC,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity,
	public AttackingNPC
{
	private:
		void setImage(Image* image);
		void ResetDrawableEntityAndSetChunk();
		bool checkCollision(double newX, double newY);

	public:
		Scorpion(int id, Spawnpoint *spawnPoint, int firstImgID);
		virtual ~Scorpion();

		void update(double dt);
		void attack();
};
