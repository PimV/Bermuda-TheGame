#pragma once
#include "Item.h"
#include "Image.h"
#include "Player.h"

class ItemCampfire :
	public Item
{
public:
	ItemCampfire(Image* image);
	void init();
	void use(Player* p);
	virtual ~ItemCampfire();
};

