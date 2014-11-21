#pragma once
#include "MenuBaseButton.h"
class MenuCreditsButton :
	public MenuBaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuCreditsButton();
	virtual ~MenuCreditsButton();
};

