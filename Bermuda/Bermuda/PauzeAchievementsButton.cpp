#include "PauzeAchievementsButton.h"
#include "PauseState.h"


PauzeAchievementsButton::PauzeAchievementsButton()
{
	init();
}

void PauzeAchievementsButton::init()
{
	std::string Message = "Achievements";
	createButton(Message);
}

void PauzeAchievementsButton::action()
{
	PauseState::Instance()->setCurWindow(1);
}

PauzeAchievementsButton::~PauzeAchievementsButton()
{
}
