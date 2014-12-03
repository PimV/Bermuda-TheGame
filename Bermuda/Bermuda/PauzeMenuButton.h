#pragma once
#include "BaseButton.h"
class PauzeMenuButton :
	public BaseButton
{
private:
	void action();

public:
	void init();

	PauzeMenuButton();
	virtual ~PauzeMenuButton();
};

