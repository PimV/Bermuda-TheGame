#include "PlayState.h"
#include "MenuState.h"
#include "GameStateManager.h"
#include <iostream>

PlayState PlayState::m_PlayState;

PlayState::PlayState(void)
{
	counter = 0;
}


void PlayState::init() {

}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {

}


void PlayState::handleEvents( GameStateManager *gsm) {
	SDL_Event mainEvent;

	if(SDL_PollEvent(&mainEvent)) {

		switch(mainEvent.type) {
		case SDL_QUIT:
			gsm->quit();
			break;

		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_SPACE:
				gsm->changeGameState(MenuState::Instance());
				break;
			case SDLK_ESCAPE:
				gsm->quit();
				break;
			}
			break;
		}
	}
}

void PlayState::update(GameStateManager *gsm, double dt) {
}

void PlayState::draw( GameStateManager *gsm) {
	//Create surface and textures
	SDL_Surface* img = SDL_LoadBMP("playstate.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->renderer, img);

	//Add texture to renderer
	SDL_RenderClear(gsm->renderer);
	SDL_RenderCopy(gsm->renderer, texture, NULL,NULL);
	SDL_RenderPresent(gsm->renderer);

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
}

PlayState::~PlayState(void)
{
}
