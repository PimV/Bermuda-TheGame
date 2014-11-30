#pragma once
#include "BaseButton.h"
class PauzeExitButton :
	public BaseButton
{
private:
	void action();

public:
	void init();

	PauzeExitButton();
	virtual ~PauzeExitButton();
};

