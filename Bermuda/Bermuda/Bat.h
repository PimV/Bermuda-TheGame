#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Bat :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Bat(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Bat();

	void update(double dt);
private:
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);

	//StateMachine<Entity>* m_pStateMachine;
	//StateMachine<Entity>* GetFSM()const{ return m_pStateMachine; }
};

