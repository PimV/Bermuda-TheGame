#pragma once
#include "header_loader.h"
#include "Ice.h"

class IceSpikes :
	public Ice
{
public:
	IceSpikes(int id, double x, double y, Image* rockImage, Image* rockPieces);
	virtual ~IceSpikes();
};

