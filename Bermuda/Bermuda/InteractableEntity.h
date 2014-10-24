#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player;
class InteractableEntity :
	virtual public Entity
{
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

	int getInteractAreaStartX();
	int getInteractAreaEndX();
	int getInteractAreaStartY();
	int getInteractAreaEndY();

	void setRangeValues();

	virtual void interact(Player* p) = 0;
	int getRangeValue();
};
