#pragma once
#include "BaseButton.h"
class MenuHelpButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructor and destructor
	MenuHelpButton();
	virtual ~MenuHelpButton();
};

