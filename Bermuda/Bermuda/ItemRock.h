#pragma once
#include "item.h"
#include "Image.h"

class ItemRock :
	public virtual Item
{
public:
	ItemRock(Image* image);

	void init();

	virtual ~ItemRock();
};

