#pragma once
#include "BaseButton.h"
class PauzeAchievementsButton :
	public BaseButton
{
private:
	void action();

public:
	void init();

	PauzeAchievementsButton();
	virtual ~PauzeAchievementsButton();
};

