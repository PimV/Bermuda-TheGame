#include "InteractableEntity.h"


InteractableEntity::InteractableEntity(void)
{
	this->rangeValue = 0;
}


InteractableEntity::~InteractableEntity(void)
{
}

void InteractableEntity::interact()
{
	// this methode is pure virtual
}

void InteractableEntity::setRangeValue(int value)
{
	this->rangeValue = value;
}

int InteractableEntity::getRangeValue()
{
	return this->rangeValue;
}
