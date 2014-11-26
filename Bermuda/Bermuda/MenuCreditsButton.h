#pragma once
#include "BaseButton.h"
class MenuCreditsButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuCreditsButton();
	virtual ~MenuCreditsButton();
};

