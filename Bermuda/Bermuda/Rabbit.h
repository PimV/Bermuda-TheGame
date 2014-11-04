#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"
#include "MovableEntity.h"

class Rabbit :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint, GameStateManager* gsm, MainEntityContainer* mec);
	~Rabbit();

	void calculateMovingDirectionAndMove(double dt);
	void update(double dt);
	bool checkCollision(CollidableContainer* container);
	void setPosition();

private:
	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	virtual void StopAnimation();
};

