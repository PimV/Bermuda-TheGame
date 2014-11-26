#include "MenuExitButton.h"


MenuExitButton::MenuExitButton()
{
	init();
}

void MenuExitButton::init()
{
	std::string Message = "Exit";
	createButton(Message, 60, 0);
}

void MenuExitButton::action()
{
	exit(0);
}

MenuExitButton::~MenuExitButton()
{
}
