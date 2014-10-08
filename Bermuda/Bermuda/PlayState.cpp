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
	p = new Player(1, 3);

	//TODO: Window resolution mee geven en correcte X en Y positie. (aan de hand van player location)
	camera = new Camera(0, 0, 640, 480);
}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {

}


void PlayState::handleEvents(GameStateManager *gsm) {
	//p->handleEvents();
	//Process Input



	//Retrieve input
	SDL_Event mainEvent;
	int x,y;

	if(SDL_PollEvent(&mainEvent)) {

		switch(mainEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			int x,y;
			SDL_GetMouseState(&x, &y);
			if (mainEvent.button.button == SDL_BUTTON_LEFT) {
				std::cout << x << "  " << y << std::endl;
				p->destX = x;
				p->destY = y;
				p->resetMovement();
				p->moveClick = true;
			}
			break;
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_LEFT:
				p->resetMovement();
				p->moveClick = false;
				p->movingLeft = true;
				p->movingRight = false;
				break;
			case SDLK_RIGHT:
				p->resetMovement();
				p->moveClick = false;
				p->movingRight = true;	
				p->movingLeft = false;
				break;
			case SDLK_UP:
				p->resetMovement();
				p->moveClick = false;
				p->movingUp = true;	
				p->movingDown = false;
				break;
			case SDLK_DOWN:
				p->resetMovement();
				p->moveClick = false;
				p->movingDown = true;	
				p->movingUp = false;	
				break;
			}
			break;

		case SDL_KEYUP:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_LEFT:
				p->moveClick = false;	
				p->movingLeft = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::West));
		
				break;
			case SDLK_RIGHT:
				p->moveClick = false;	
				p->movingRight = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::East));
				
				break;
			case SDLK_UP:
				p->moveClick = false;	
				p->movingUp = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::North));

				break;
			case SDLK_DOWN:
				p->moveClick = false;	
				p->movingDown = false;
				break;
			}
			break;
		}
	}
}

void PlayState::update(GameStateManager *gsm, double dt) {
	gsm->getActionContainer()->executeAllActions(dt);
	p->move(dt);
}

void PlayState::draw(GameStateManager *gsm) {
	gsm->sdlInitializer->clearScreen();

	//Draw player
	p->draw(gsm->sdlInitializer);

	//Draw drawable container


	gsm->sdlInitializer->drawScreen();
}

PlayState::~PlayState(void)
{
	delete camera;
}
