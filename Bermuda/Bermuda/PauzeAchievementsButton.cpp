#include "PauzeAchievementsButton.h"
#include "PauseState.h"


PauzeAchievementsButton::PauzeAchievementsButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeAchievementsButton::init(GameStateManager* gsm)
{
	std::string Message = "Achievements";
	createButton(Message);
}

void PauzeAchievementsButton::action(GameStateManager* gsm)
{
	PauseState::Instance()->setCurWindow(1);
}

PauzeAchievementsButton::~PauzeAchievementsButton()
{
}
