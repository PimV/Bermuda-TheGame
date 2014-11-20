#include "MenuPlayButton.h"


MenuPlayButton::MenuPlayButton()
{
	init();
}

void MenuPlayButton::init()
{
	std::string Message = "Play";
	createButton(Message);
}

void MenuPlayButton::action()
{
	GameStateManager::Instance()->changeGameState(PlayState::Instance());
}

MenuPlayButton::~MenuPlayButton()
{
}
