#pragma once
#include "item.h"
#include "Image.h"

class ItemWood :
	public virtual Item
{
public:
	ItemWood(Image* image);

	void init();

	virtual ~ItemWood();
};

