#pragma once
#include "BaseButton.h"
#include "MenuState.h"

class MenuMainButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuMainButton();
	virtual ~MenuMainButton();
};

