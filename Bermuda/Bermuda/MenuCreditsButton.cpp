#include "MenuCreditsButton.h"
#include "MenuState.h"


MenuCreditsButton::MenuCreditsButton()
{
	init();
}

void MenuCreditsButton::init()
{
	std::string Message = "Credits";
	createButton(Message);
}

void MenuCreditsButton::action()
{
	MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuCreditsScreen());
}

MenuCreditsButton::~MenuCreditsButton()
{
}
