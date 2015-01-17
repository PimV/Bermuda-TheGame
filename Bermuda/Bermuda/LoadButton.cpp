#include "LoadButton.h"


LoadButton::LoadButton(MenuLoadScreen* loadScreen)
{
	this->loadScreen = loadScreen;
}

bool LoadButton::clicked(int x, int y)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		return true;
	}
	return false;
}

LoadButton::~LoadButton()
{
}
