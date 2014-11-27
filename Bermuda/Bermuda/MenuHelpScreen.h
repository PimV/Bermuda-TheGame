#pragma once
#include "BaseScreen.h"
class MenuHelpScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* tempTexture;
	SDL_Rect tempRect;
	SDL_Texture* temp2Texture;
	SDL_Rect temp2Rect;

	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuHelpScreen();
	virtual ~MenuHelpScreen();
};

