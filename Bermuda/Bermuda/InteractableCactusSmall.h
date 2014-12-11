#pragma once
#include "header_loader.h"
#include "InteractableCactus.h"

class InteractableCactusSmall :
	public InteractableCactus
{
public:
	InteractableCactusSmall(int id, double x, double y, Image* cactusImage, Image* stumpImage);
	virtual ~InteractableCactusSmall();
};

