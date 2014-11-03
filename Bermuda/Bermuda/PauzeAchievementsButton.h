#pragma once
#include "BasePauzeButton.h"
class PauzeAchievementsButton :
	public BasePauzeButton
{
private:
	void action(GameStateManager* gsm);

public:
	void init(GameStateManager* gsm);

	PauzeAchievementsButton(GameStateManager* gsm);
	virtual ~PauzeAchievementsButton();
};

