#pragma once
#include "item.h"
#include "Tool.h"
#include "Image.h"
enum class Items;

class ToolFlint :
	public Tool
{
public:
	ToolFlint(Image* image);

	void init();
	void equip(Player* player);

	virtual ~ToolFlint();
};

