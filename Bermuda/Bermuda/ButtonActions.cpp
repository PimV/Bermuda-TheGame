#include "ButtonActions.h"

void setCreditsScreenAction()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuCreditsScreen());
}

void exitAction()
{
	exit(0);
}

void menuSetHelpScreenAction()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuHelpScreen());
}

void playAction()
{
	GameStateManager::Instance()->changeGameState(PlayState::Instance());
}

void pauseSetAchievementScreenAction()
{
	PauseState::Instance()->setCurWindow(PauseState::Instance()->getMainAchievementsScreen());
}

void backToMenuAction()
{
	GameStateManager::Instance()->changeGameState(MenuState::Instance());
}

void resumeGameAction()
{
	GameStateManager::Instance()->popState();
}

void menuMainScreenAction()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuMainScreen());
}

void helpMovementScreenAction(MenuHelpScreen* helpScr)
{
	helpScr->setCurWindow(helpScr->getMovementScr());
}