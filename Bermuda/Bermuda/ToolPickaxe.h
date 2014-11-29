#pragma once
#include "Tool.h"
#include "Image.h"

class ToolPickaxe :
	public Tool
{
public:
	ToolPickaxe(Image* image);

	void init();

	virtual ~ToolPickaxe();
};

