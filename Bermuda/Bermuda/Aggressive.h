#pragma once
#include "ibehaviour.h"
class Aggressive :
	public IBehaviour
{
public:
	virtual ~Aggressive(void);
	void behave();
};