#pragma once
#include "BasePauzeButton.h"
class PauzeMenuButton :
	public BasePauzeButton
{
private:
	void action(GameStateManager* gsm);

public:
	void init(GameStateManager* gsm);

	PauzeMenuButton(GameStateManager* gsm);
	virtual ~PauzeMenuButton();
};

