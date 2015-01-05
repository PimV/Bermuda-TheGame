#pragma once
#include "BaseButton.h"
#include "MenuLoadScreen.h"

class LoadButton :
	public BaseButton
{
private:
	MenuLoadScreen* loadScreen;
public:
	bool clicked(int x, int y);

	LoadButton(MenuLoadScreen* loadScreen);
	virtual ~LoadButton();
};

