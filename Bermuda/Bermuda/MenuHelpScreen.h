#pragma once
#include "BaseScreen.h"
#include "BaseHelpScreen.h"
#include "BaseButton.h"

class MenuHelpScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* firstTexture;
	SDL_Rect firstRect;
	SDL_Rect secRect;
	SDL_Texture* secTexture;
	std::vector<BaseButton*> buttons;

	BaseHelpScreen* curWindow;
	BaseHelpScreen* movementScreen;
	BaseHelpScreen* cutTreeScreen;
	BaseHelpScreen* mineRockScreen;

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
	BaseHelpScreen* getMineRockScr();

	//constructors destructors
	MenuHelpScreen();
	virtual ~MenuHelpScreen();
};

