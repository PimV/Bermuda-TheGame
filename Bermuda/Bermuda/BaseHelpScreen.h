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
	SDL_Rect picturePortraitRect;
	SDL_Texture* picturePortraitTexture;
	int textMaxWidth;
	int textMaxHeight;
	SDL_Rect textRect;
	SDL_Texture* textTexture;
	SDL_Rect textPortraitRect;
	SDL_Texture* textPortraitTexture;

public:
	//Methodes
	void draw();
	void setPicture(std::string pictureLocation);
	void setText(std::string text);
	
	//constructor destructor
	BaseHelpScreen(int x);
	virtual ~BaseHelpScreen();
};

