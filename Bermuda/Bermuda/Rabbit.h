#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "IMovable.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Rabbit :
	public NPC,
	public Evasive,
	public IMovable,
	public DrawableEntity
{
public:
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint, GameStateManager* gsm, MainEntityContainer* mec);
	~Rabbit();

	void walk(double dt);
	void move(double dt, double destinationX, double destinationY);
	void update(double dt);

private:
	int firstImgID, tempCounter, dx, dy, maxSpeed, stopSpeed;
	bool walking, movingDown, movingUp, movingRight, movingLeft;
};

