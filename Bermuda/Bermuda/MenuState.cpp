#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include <iostream>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
	counter = 0;
}

void MenuState::init() {
	SDL_Surface* temp = SDL_LoadBMP("menustate.bmp");

	bg = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_UNKNOWN, 0);

	SDL_FreeSurface(temp);
}

void MenuState::cleanup() {
	SDL_FreeSurface(bg);
}

void MenuState::pause() {

}

void MenuState::resume() {

}


void MenuState::handleEvents( GameStateManager *gsm) {
	SDL_Event mainEvent;

	if(SDL_PollEvent(&mainEvent)) {
		switch(mainEvent.type) {
		case SDL_QUIT:
			gsm->quit();
			break;

		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_SPACE:
				gsm->changeGameState(PlayState::Instance());
				break;
			case SDLK_ESCAPE:
				gsm->quit();
				break;
			}
			break;
		}
	}
}

void MenuState::update(GameStateManager *gsm, double dt) {
	//std::cout << "Pim rocks " << counter <<  std::endl;
}

void MenuState::draw(GameStateManager *gsm) {
	//Create surface and textures
	SDL_Surface* img = SDL_LoadBMP("menustate.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->renderer, img);

	//Add texture to renderer
	SDL_RenderClear(gsm->renderer); //clear screen
	SDL_RenderCopy(gsm->renderer, texture, NULL,NULL); //draw texture
	SDL_RenderPresent(gsm->renderer); //present screen

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
}



MenuState::~MenuState(void)
{
}
