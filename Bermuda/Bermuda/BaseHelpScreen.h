#pragma once
#include "header_loader.h"
#include "GameStateManager.h"

class BaseHelpScreen
{
private:
	//Variables
	int startXPos;
	int screenWidth;
	SDL_Rect pictureRect;
	SDL_Texture* pictureTexture;
	SDL_Rect textRect;
	SDL_Texture* textTexture;

public:
	//Methodes
	void draw();
	void setPicture();
	void setText();
	
	//constructor destructor
	BaseHelpScreen(int x);
	virtual ~BaseHelpScreen();
};

