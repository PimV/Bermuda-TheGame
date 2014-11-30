#pragma once
#include "BaseButton.h"
class PauzeResumeButton :
	public BaseButton
{
private:
	void action();

public:
	void init();

	PauzeResumeButton();
	virtual ~PauzeResumeButton();
};

