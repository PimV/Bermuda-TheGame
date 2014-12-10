#pragma once
#include "Tool.h"
#include "Image.h"

class ToolGoldenAxe :
	public Tool
{
public:
	ToolGoldenAxe(Image* image);

	void init();

	virtual ~ToolGoldenAxe();
};

