#pragma once
#include "PauzeBaseButton.h"
class PauzeMenuButton :
	public PauzeBaseButton
{
private:
	void action();

public:
	void init();

	PauzeMenuButton();
	virtual ~PauzeMenuButton();
};

