#pragma once
#include "header_loader.h"
#include "InteractableCactus.h"

class InteractableCactusBig :
	public InteractableCactus
{
public:
	InteractableCactusBig(int id, double x, double y, Image* cactusImage, Image* stumpImage);
	virtual ~InteractableCactusBig();
};

