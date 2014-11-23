#pragma once
#include "Item.h"
#include "Player.h"
#include "Entity.h"

class Placeable :
	public Item
{
private:
	Entity* placeEntity;
public:
	Placeable();
	void setPlaceEntity(Entity* entity);
	void Use(Player* p);
	virtual ~Placeable();
};

