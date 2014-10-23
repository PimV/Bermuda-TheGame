#pragma once

class InteractableEntity
{
public:
	InteractableEntity(void);
	virtual ~InteractableEntity(void);

	virtual void interact() = 0;
	virtual void setRangeValue(int value);
	virtual int getRangeValue();

private:
	int rangeValue;
};
