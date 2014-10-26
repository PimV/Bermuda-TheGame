#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player;
class GameStateManager;
class InteractableEntity :
	virtual public Entity
{
protected:
	bool destroyed;
	long interactTime;
	long timeSinceDestroy;
	long respawnTime;
	long currentInteractTime;

private:
	int rangeValue;
	int startX;
	int endX;
	int startY;
	int endY;

public:
	InteractableEntity(int id, double x, double y, int chunkSize, int rangeValue);

	virtual void update(double dt) = 0;

	virtual ~InteractableEntity();

	bool trackInteractTimes();

	int getInteractAreaStartX();
	int getInteractAreaEndX();
	int getInteractAreaStartY();
	int getInteractAreaEndY();

	void setRangeValues();

	//virtual void interact(Player* p) = 0;
	virtual void interact(Player* p);
	int getRangeValue();
};
