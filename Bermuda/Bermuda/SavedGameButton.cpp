#include "SavedGameButton.h"


SavedGameButton::SavedGameButton(MenuLoadScreen* loadScreen, std::string fileName)
{
	this->loadScreen = loadScreen;
	this->fileName = fileName;
}

bool SavedGameButton::clicked(int x, int y)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		if (this->fileName != "")
		{
			this->loadScreen->setCurrentFileToLoad(this->fileName);
			return true;
		}
	}
	return false;
}

SavedGameButton::~SavedGameButton()
{
}
