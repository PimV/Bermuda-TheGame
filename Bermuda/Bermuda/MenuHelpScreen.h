#pragma once
#include "BaseScreen.h"
#include "BaseHelpScreen.h"
#include "BaseButton.h"

class MenuHelpScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* tempTexture;
	SDL_Rect tempRect;
	std::vector<BaseButton*> buttons;

	BaseHelpScreen* curWindow;
	BaseHelpScreen* movementScreen;
	BaseHelpScreen* cutTreeScreen;

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
	BaseHelpScreen* getMovementScr();
	BaseHelpScreen* getCutTreeScr();

	//constructors destructors
	MenuHelpScreen();
	virtual ~MenuHelpScreen();
};

