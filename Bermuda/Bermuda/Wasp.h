#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"
#include "MovableEntity.h"

class Wasp :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Wasp(int id, int chunkSize, Spawnpoint *spawnPoint);
	~Wasp();

	void walk(double dt);
	void update(double dt);
	bool checkCollision(CollidableContainer* container);
	void setPosition();

private:
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	GameStateManager* gsm;
	MainEntityContainer* mec;

	int firstImgID;
	long timeSinceLastAction;
};

