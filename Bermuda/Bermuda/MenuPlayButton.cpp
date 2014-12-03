#include "MenuPlayButton.h"


MenuPlayButton::MenuPlayButton()
{
	init();
}

void MenuPlayButton::init()
{
	std::string Message = "Play";
	createButton(Message, 60, 0);
}

void MenuPlayButton::action()
{
	GameStateManager::Instance()->changeGameState(PlayState::Instance());
}

MenuPlayButton::~MenuPlayButton()
{
}
