#pragma once
#include "Tool.h"
#include "Image.h"

class ToolFlint :
	public Tool
{
public:
	ToolFlint(Image* image);

	void init();

	virtual ~ToolFlint();
};

