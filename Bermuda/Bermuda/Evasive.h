#pragma once
#include "ibehaviour.h"
class Evasive :
	public IBehaviour
{
public:
	virtual ~Evasive(void);
	void behave();
};

