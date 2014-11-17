#include "PauzeExitButton.h"

PauzeExitButton::PauzeExitButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeExitButton::init(GameStateManager* gsm)
{
	std::string Message = "Save and exit";
	createButton(Message);
}

void PauzeExitButton::action(GameStateManager* gsm)
{
	exit(0);
}

PauzeExitButton::~PauzeExitButton()
{
}
