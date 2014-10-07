#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include <iostream>

PlayState PlayState::m_PlayState;

PlayState::PlayState(void)
{
}


void PlayState::init() {
	p = new Player(1, 5);
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
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_LEFT:
				gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::West));
				/*std::cout << "Left Pressed" << std::endl;*/
				break;
			case SDLK_RIGHT:
				gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::East));
				std::cout << "Right Pressed" << std::endl;
				break;
			case SDLK_UP:
				gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::North));
				std::cout << "Up Pressed" << std::endl;
				break;
			case SDLK_DOWN:
				gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::South));
				std::cout << "Down Pressed" << std::endl;
				break;
			}
			break;
		}
	}
}

void PlayState::update(GameStateManager *gsm, double dt) {
}

void PlayState::draw(GameStateManager *gsm) {
	////Create surface and textures
	//SDL_Surface* img = SDL_LoadBMP("playstate.bmp");
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), img);

	//Button* b = new Button(15,15,50,50,"HOOI");

	////Add texture to renderer
	//gsm->sdlInitializer->clearScreen();


	//gsm->sdlInitializer->drawTexture(texture, NULL);
	//gsm->sdlInitializer->drawTexture(texture, &b->getRectangle());

	//gsm->sdlInitializer->drawScreen();

	////Clean created textures/surfaces
	//SDL_DestroyTexture(texture);  
	//SDL_FreeSurface(img); 
	//delete b;
}

PlayState::~PlayState(void)
{
}
