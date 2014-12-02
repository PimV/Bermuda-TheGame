#pragma once
#include "Item.h"
#include "Image.h"
#include "Player.h"
#include "ParticleEngine.h"

class ItemCampfire :
	public Item
{

private:

public:

	ItemCampfire(Image* image);
	void init();
	void use(Player* p);
	virtual ~ItemCampfire();
};

