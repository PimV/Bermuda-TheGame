#pragma once
#include "Tool.h"
#include "Image.h"

class ToolAxe :
	public Tool
{
public:
	ToolAxe(Image* image);

	void init();

	virtual ~ToolAxe();
};

