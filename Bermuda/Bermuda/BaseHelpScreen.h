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
	int textMaxWidth;
	int textMaxHeight;
	SDL_Rect textRect;
	SDL_Texture* textTexture;

public:
	//Methodes
	void draw();
	void setPicture(std::string pictureLocation);
	void setText(std::string text);
	
	//constructor destructor
	BaseHelpScreen(int x);
	virtual ~BaseHelpScreen();
};

