#pragma once
#include "BaseScreen.h"
#include "BaseHelpScreen.h"

class MenuHelpScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* tempTexture;
	SDL_Rect tempRect;

	BaseHelpScreen* curWindow;
	BaseHelpScreen* tempScreen;

	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//Methodes		Screens
	void setCurWindow(BaseHelpScreen* curwindow);

	//constructors destructors
	MenuHelpScreen();
	virtual ~MenuHelpScreen();
};

