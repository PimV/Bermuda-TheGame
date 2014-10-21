#include "InteractiveBase.h"


InteractiveBase::InteractiveBase(void)
{
	this->rangeValue = 0;
}


InteractiveBase::~InteractiveBase(void)
{
}

void InteractiveBase::interact()
{
	// TODO: Fill methode
}

void InteractiveBase::setRangeValue(int value)
{
	this->rangeValue = value;
}

int InteractiveBase::getRangeValue()
{
	return this->rangeValue;
}