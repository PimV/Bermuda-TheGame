#pragma once
#include "BaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class MenuExitButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuExitButton();
	virtual ~MenuExitButton();
};

