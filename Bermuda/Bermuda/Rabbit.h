#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
#include "HealthEntity.h"

class Rabbit :
	public NPC,
	public Evasive,
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity,
	public InteractableEntity,
	public HealthEntity
{
public:
	Rabbit(int id, Spawnpoint *spawnPoint, int firstImgID);
	virtual ~Rabbit();

	void update(double dt);
	bool checkCollision(double newX, double newY);

	//Interact methods
	void interact(Player* player);
	void setDestroyedState();
	void draw(Camera* camera, SDL_Renderer* renderer);

private:
	void directionsAndMove(double dt);
	
	// Replace methods to DrawableEntity & CollidableEntity
	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
};
