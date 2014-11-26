#include "MenuHelpButton.h"
#include "MenuState.h"

MenuHelpButton::MenuHelpButton()
{
	init();
}

void MenuHelpButton::init()
{
	std::string Message = "Help";
	createButton(Message, 60, 0);
}

void MenuHelpButton::action()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuHelpScreen());
}


MenuHelpButton::~MenuHelpButton()
{
}
