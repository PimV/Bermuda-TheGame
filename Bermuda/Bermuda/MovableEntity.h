#pragma once
#include "entity.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity(void);
};

