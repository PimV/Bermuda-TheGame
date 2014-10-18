#pragma once
#include <SDL.h>

class InteractiveBase
{
public:
	InteractiveBase(void);
	virtual ~InteractiveBase(void);

	virtual void interact();
	virtual void setRangeValue(int value) = 0;
	virtual int getRangeValue() = 0;

private:
	int rangeValue;

	virtual void createRangeRect() = 0;
};

