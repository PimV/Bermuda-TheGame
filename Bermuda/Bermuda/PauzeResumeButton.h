#pragma once
#include "BasePauzeButton.h"
class PauzeResumeButton :
	public BasePauzeButton
{
private:
	void action();

public:
	void init();

	PauzeResumeButton();
	virtual ~PauzeResumeButton();
};

