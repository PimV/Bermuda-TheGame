#pragma once
#include "ExitButton.h"
#include "PlayButton.h"
#include <SDL_image.h>
#include <SDL.h>
#include "igamestate.h"
#include "header_loader.h"
class MenuState :
	public IGameState
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	static const int totalButtons = 2;

	static MenuState m_MenuState;

	GameStateManager* gsm;

	SDL_Surface* bg;
	int alpha;

public:
	//TODO: put buttons in array
	PlayButton* playButton;
	ExitButton* exitButton;

	void align();

	MenuState(void);
	void init(GameStateManager *gsm) ;
	void cleanup();

	void pause();
	void resume();

	void handleEvents() ;
	void update(double dt) ;
	void draw() ;

	static MenuState* Instance() {
		return &m_MenuState;
	}

	~MenuState(void);
};

