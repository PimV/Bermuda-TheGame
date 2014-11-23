#pragma once
#include "Placeable.h"
#include "Image.h"

class ItemCampfire :
	public Placeable
{
public:
	ItemCampfire(Image* image);
	void init();
	virtual ~ItemCampfire();
};

