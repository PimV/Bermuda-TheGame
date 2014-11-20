#pragma once
#include "PauzeBaseButton.h"
class PauzeAchievementsButton :
	public PauzeBaseButton
{
private:
	void action();

public:
	void init();

	PauzeAchievementsButton();
	virtual ~PauzeAchievementsButton();
};

