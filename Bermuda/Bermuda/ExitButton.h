#pragma once
#include "BaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class ExitButton :
	public BaseButton
{
public:
	//methodes
	void init();
	void action();

	//Constructors and destructors
	ExitButton();
	virtual ~ExitButton();
};

