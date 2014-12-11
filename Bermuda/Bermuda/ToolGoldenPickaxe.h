#pragma once
#include "Tool.h"
#include "Image.h"

class ToolGoldenPickaxe :
	public Tool
{
public:
	ToolGoldenPickaxe(Image* image);

	void init();

	virtual ~ToolGoldenPickaxe();
};

