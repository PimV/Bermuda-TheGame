#pragma once
#include "PauzeBaseButton.h"
class PauzeExitButton :
	public PauzeBaseButton
{
private:
	void action();

public:
	void init();

	PauzeExitButton();
	virtual ~PauzeExitButton();
};

