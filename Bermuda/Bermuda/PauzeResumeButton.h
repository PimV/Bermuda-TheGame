#pragma once
#include "PauzeBaseButton.h"
class PauzeResumeButton :
	public PauzeBaseButton
{
private:
	void action();

public:
	void init();

	PauzeResumeButton();
	virtual ~PauzeResumeButton();
};

