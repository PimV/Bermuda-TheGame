#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include <iostream>

PlayState PlayState::m_PlayState;

PlayState::PlayState(void)
{
}


void PlayState::init() {

}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {

}


void PlayState::handleEvents(GameStateManager *gsm) {
	//Process Input
	gsm->getActionContainer()->executeAllActions();


	//Retrieve input
	SDL_Event mainEvent;
	int x,y;

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
		case SDL_MOUSEMOTION: 

			SDL_GetMouseState(&x, &y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&x, &y);
			if (mainEvent.button.button == SDL_BUTTON_LEFT) {
				gsm->getActionContainer()->addAction(new ClickAction(x, y));
			}
			break;
		}
	}
}

void PlayState::update(GameStateManager *gsm, double dt) {
}

void PlayState::draw(GameStateManager *gsm) {
	//Create surface and textures
	SDL_Surface* img = SDL_LoadBMP("playstate.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), img);

	Button* b = new Button(15,15,50,50,"HOOI");

	//Add texture to renderer
	gsm->sdlInitializer->clearScreen();


	gsm->sdlInitializer->drawTexture(texture, NULL);
	gsm->sdlInitializer->drawTexture(texture, &b->getRectangle());

	gsm->sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
	delete b;
}

PlayState::~PlayState(void)
{
}
