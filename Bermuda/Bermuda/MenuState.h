#pragma once
#include "MenuExitButton.h"
#include "MenuPlayButton.h"
#include <SDL_image.h>
#include <SDL.h>
#include "igamestate.h"
#include "header_loader.h"
class MenuState :
	public IGameState
{
private:
	//variables		textures and rectangles
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	SDL_Texture* bermudaTextTexture;
	SDL_Rect bermudaTextRect;

	//variables buttons
	std::vector<MenuBaseButton*> buttons;

	//self
	static MenuState m_MenuState;

public:
	//TODO: put buttons in array

	//Methodes
	void align();
	void pause();								//unused
	void resume();								//unused
	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt) ;
	void draw() ;

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

