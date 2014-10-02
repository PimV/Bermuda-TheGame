#pragma once
#include "iaction.h"
class ClickAction :
	public IAction
{
public:
	ClickAction(double x, double y);

	void execute();

	virtual ~ClickAction(void);
private:
	double x;
	double y;
};

