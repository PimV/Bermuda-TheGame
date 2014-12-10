#pragma once
#include "item.h"
#include "Image.h"

class ItemBranch :
	public virtual Item
{
public:
	ItemBranch(Image* image);

	void init();

	virtual ~ItemBranch();
};

