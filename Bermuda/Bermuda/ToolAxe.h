#pragma once
#include "item.h"
#include "Tool.h"
#include "Image.h"
enum class Items;

class ToolAxe :
	public Tool
{
public:
	ToolAxe(Image* image);

	void init(Image* image);
	void equip(Player* player);

	virtual ~ToolAxe();
};

