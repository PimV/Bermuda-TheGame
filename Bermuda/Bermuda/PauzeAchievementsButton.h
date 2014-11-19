#pragma once
#include "BasePauzeButton.h"
class PauzeAchievementsButton :
	public BasePauzeButton
{
private:
	void action();

public:
	void init();

	PauzeAchievementsButton();
	virtual ~PauzeAchievementsButton();
};

