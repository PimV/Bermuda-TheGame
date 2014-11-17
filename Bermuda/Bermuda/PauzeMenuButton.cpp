#include "PauzeMenuButton.h"
#include "MenuState.h"


PauzeMenuButton::PauzeMenuButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeMenuButton::init(GameStateManager* gsm)
{
	std::string Message = "Save and back to menu";
	createButton(Message);
}

void PauzeMenuButton::action(GameStateManager* gsm)
{
	gsm->changeGameState(MenuState::Instance());
}

PauzeMenuButton::~PauzeMenuButton()
{
}
