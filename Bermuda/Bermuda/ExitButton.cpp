#include "ExitButton.h"


ExitButton::ExitButton()
{
	init();
}

void ExitButton::init()
{
	std::string Message = "Exit";
	createButton(Message);
}

void ExitButton::action()
{
	exit(0);
}

ExitButton::~ExitButton()
{
}
