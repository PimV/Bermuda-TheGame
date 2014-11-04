#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "IMovable.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Wasp :
	public NPC,
	public Evasive,
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Wasp(int id, int chunkSize, Spawnpoint *spawnPoint, int firstImgID);
	~Wasp();

	void walk(double dt);
	virtual void move(double dt);
	void update(double dt);
	bool checkCollision(CollidableContainer* container);
	void setPosition();

private:
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	GameStateManager* gsm;
	MainEntityContainer* mec;

	int firstImgID;
	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;

	int dx, dy, stopSpeed;
	bool movingDown, movingUp, movingRight, movingLeft;

	double maxSpeed;
	long timeSinceLastAction;
};

