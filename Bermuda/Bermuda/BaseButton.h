#pragma once
#include <SDL.h>
#include "header_loader.h"
#include <string>
#include "GameStateManager.h"

class BaseButton
{
public:
	//variables
	int PosY;
	int position;
	bool active;

protected:
	//variables
	SDL_Texture* buttonTexture;
	SDL_Texture* buttonHoverTexture;
	SDL_Rect buttonRect;

	//virtual methodes
	virtual void action() = 0;

public:
	//variables
	static const int ConstHeight = 80;
	static const int ConstWidth = 260;
	static const int PosX = 30;		//TODO: write Y position calc
	void createButton(std::string);
	
	//methodes
	void placeAbove(BaseButton* button);
	void placeUnder(BaseButton* button);
	void draw();
	void hover(int, int);
	bool clicked(int, int);

	BaseButton();
	virtual void init() = 0;
	void cleanup();
	virtual ~BaseButton();
};

