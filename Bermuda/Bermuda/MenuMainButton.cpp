#include "MenuMainButton.h"


MenuMainButton::MenuMainButton()
{
	init();
}

void MenuMainButton::init()
{
	std::string Message = "Return to main menu";
	createButton(Message, 40);
}

void MenuMainButton::action()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuMainScreen());
}

MenuMainButton::~MenuMainButton()
{
}
