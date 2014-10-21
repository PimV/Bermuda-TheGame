#pragma once

class InteractiveBase
{
public:
	InteractiveBase(void);
	virtual ~InteractiveBase(void);

	virtual void interact() = 0;
	virtual void setRangeValue(int value);
	virtual int getRangeValue();

private:
	int rangeValue;
};
