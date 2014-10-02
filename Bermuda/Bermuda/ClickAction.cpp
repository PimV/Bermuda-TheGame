#include "ClickAction.h"
#include <iostream>


ClickAction::ClickAction(double x, double y)
{
	this->x = x;
	this->y = y;
}

void ClickAction::execute() {
	std::cout << "Executing Click Action on coords:" << x << ":" << y << std::endl;
}



ClickAction::~ClickAction(void)
{
}
