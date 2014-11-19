#include "PauzeMenuButton.h"
#include "MenuState.h"


PauzeMenuButton::PauzeMenuButton()
{
	init();
}

void PauzeMenuButton::init()
{
	std::string Message = "Save and back to menu";
	createButton(Message);
}

void PauzeMenuButton::action()
{
	GameStateManager::Instance()->changeGameState(MenuState::Instance());
}

PauzeMenuButton::~PauzeMenuButton()
{
}
