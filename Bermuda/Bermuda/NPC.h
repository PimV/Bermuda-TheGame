#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "InteractableEntity.h"
class Player;

class NPC :
	public virtual Entity
	//public InteractableEntity
{
public:
	NPC(int id, Spawnpoint *spawnPoint);
	virtual ~NPC();

	Spawnpoint* getSpawnPoint();
	void setSpawnPoint(Spawnpoint *spawnPoint);

	void interact(Player* player);

protected:
	Spawnpoint *spawnPoint;

private:

};
