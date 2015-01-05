#pragma once
#include "BaseButton.h"
#include "MenuLoadScreen.h"

class SavedGameButton :
	public BaseButton
{
private:
	MenuLoadScreen* loadScreen;
	std::string fileName;

public:
	bool clicked(int x, int y);


	SavedGameButton(MenuLoadScreen* loadScreen, std::string fileName);
	virtual ~SavedGameButton();
};

