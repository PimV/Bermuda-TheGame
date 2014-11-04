#pragma once
#include "BasePauzeButton.h"
class PauzeResumeButton :
	public BasePauzeButton
{
private:
	void action(GameStateManager* gsm);

public:
	void init(GameStateManager* gsm);

	PauzeResumeButton(GameStateManager* gsm);
	virtual ~PauzeResumeButton();
};

