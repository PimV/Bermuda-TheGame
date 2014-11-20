#pragma once
#include "BasePauzeButton.h"
class PauzeExitButton :
	public BasePauzeButton
{
private:
	void action();

public:
	void init();

	PauzeExitButton();
	virtual ~PauzeExitButton();
};

