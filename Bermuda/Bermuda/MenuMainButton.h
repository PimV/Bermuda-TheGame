#pragma once
#include "MenuBaseButton.h"
#include "MenuState.h"

class MenuMainButton :
	public MenuBaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuMainButton();
	virtual ~MenuMainButton();
};

