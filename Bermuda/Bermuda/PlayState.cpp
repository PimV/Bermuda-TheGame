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
	//TODO: Window resolution mee geven en correcte X en Y positie. (aan de hand van player location)
	camera = new Camera(0, 0, 640, 480);
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
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), img);

	//Add texture to renderer
	gsm->sdlInitializer->drawTexture(texture);

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
}

PlayState::~PlayState(void)
{
	delete camera;
}
