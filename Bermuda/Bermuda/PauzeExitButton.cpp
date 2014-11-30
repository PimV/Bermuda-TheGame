#include "PauzeExitButton.h"

PauzeExitButton::PauzeExitButton()
{
	init();
}

void PauzeExitButton::init()
{
	std::string Message = "Save and exit";
	createButton(Message, 24, 1);
}

void PauzeExitButton::action()
{
	exit(0);
}

PauzeExitButton::~PauzeExitButton()
{
}
