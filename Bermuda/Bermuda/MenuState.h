#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "igamestate.h"
#include "header_loader.h"
#include "MenuMainScreen.h"
#include "MenuCreditsScreen.h"
#include "MenuHelpScreen.h"

class MenuState :
	public IGameState
{
private:
	//variables		Screens
	BaseScreen* curScreen;
	MenuMainScreen* mainScr;
	MenuCreditsScreen* creditsScr;
	MenuHelpScreen* helpScr;

	//self
	static MenuState m_MenuState;

public:
	//Methodes
	void pause();								//unused
	void resume();								//unused
	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt) ;
	void draw() ;

	//Methodes		Screens
	void setCurWindow(BaseScreen* curwindow);
	BaseScreen* getMenuMainScreen();
	BaseScreen* getMenuCreditsScreen();
	BaseScreen* getMenuHelpScreen();

	//Get instance self
	static MenuState* Instance() {
		return &m_MenuState;
	}

	//constructors destructors etc
	MenuState();
	void init(GameStateManager *gsm) ;
	void cleanup();
	~MenuState(void);
};

