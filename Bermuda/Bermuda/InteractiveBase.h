#pragma once
#include <SDL.h>

class InteractiveBase
{
public:
	InteractiveBase(void);
	virtual ~InteractiveBase(void);

	virtual void interact();
	virtual void setRangeValue(int value);
	virtual int getRangeValue();

private:
	int rangeValue;
};

