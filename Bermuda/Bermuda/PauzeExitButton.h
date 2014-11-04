#pragma once
#include "BasePauzeButton.h"
class PauzeExitButton :
	public BasePauzeButton
{
private:
	void action(GameStateManager* gsm);

public:
	void init(GameStateManager* gsm);

	PauzeExitButton(GameStateManager* gsm);
	virtual ~PauzeExitButton();
};

