#pragma once
#include "BasePauzeButton.h"
class PauzeMenuButton :
	public BasePauzeButton
{
private:
	void action();

public:
	void init();

	PauzeMenuButton();
	virtual ~PauzeMenuButton();
};

