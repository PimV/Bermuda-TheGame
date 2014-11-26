#pragma once
#include "BaseScreen.h"
class MenuHelpScreen :
	public BaseScreen
{
private:

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

