#pragma once
#include "Entity.h"
class LightEntity :
	public virtual Entity
{
public:
	LightEntity(int id, double x, double y);
	virtual ~LightEntity();

	bool getShining();
	void setShining(bool NewItem);
private:
	bool shining;
};

