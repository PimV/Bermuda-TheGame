#pragma once
#include "MenuBaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class MenuExitButton :
	public MenuBaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructors and destructors
	MenuExitButton();
	virtual ~MenuExitButton();
};

