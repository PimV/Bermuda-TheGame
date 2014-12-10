#pragma once
#include "header_loader.h"
#include "Ice.h"

class IceRock :
	public Ice
{
public:
	IceRock(int id, double x, double y, Image* rockImage, Image* rockPieces);
	virtual ~IceRock();
};

