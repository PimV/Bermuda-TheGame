#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
class BaseBehaviour;
class Player;

class NPC :
	public virtual Entity
{
	private:
		Spawnpoint *spawnPoint;

	protected:
		BaseBehaviour* behaviour;

	public:
		NPC(int id, int actionRange, int attackRange, Spawnpoint *spawnPoint);
		virtual ~NPC();

		Spawnpoint* getSpawnPoint();
		BaseBehaviour* getBehaviour();

		void setSpawnPoint(Spawnpoint *spawnPoint);
};
