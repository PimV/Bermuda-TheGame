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
	SDL_Texture* buttonImage;
	SDL_Rect buttonRect;
	std::string normalPicture;
	std::string hoverPicure;

	//virtual methodes
	virtual void loadHoverPicture(GameStateManager *gsm) = 0;
	virtual void loadNormalPicture(GameStateManager *gsm) = 0;
	virtual void action(GameStateManager *gsm) = 0;

public:
	//variables
	static const int ConstHeight = 80;
	static const int ConstWidth = 260;
	static const int PosX = 30;		//TODO: write Y position calc
	
	//methodes
	void align(int, int);
	void draw(GameStateManager *gsm);
	void hover(int, int, GameStateManager *gsm);
	void clicked(int, int, GameStateManager *gsm);

	BaseButton();
	virtual ~BaseButton();
};

