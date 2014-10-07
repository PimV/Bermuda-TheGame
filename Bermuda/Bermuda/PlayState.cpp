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
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_LEFT:
				p->movingLeft = true;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::West));
		
				break;
			case SDLK_RIGHT:
				p->movingRight = true;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::East));
		
				break;
			case SDLK_UP:
				p->movingUp = true;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::North));
		
				break;
			case SDLK_DOWN:
				p->movingDown = true;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::South));
		
				break;
			}
			break;

		case SDL_KEYUP:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_LEFT:
				p->movingLeft = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::West));
		
				break;
			case SDLK_RIGHT:
				p->movingRight = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::East));
				
				break;
			case SDLK_UP:
				p->movingUp = false;
				//gsm->getActionContainer()->addAction(new MoveAction(p, EnumDirection::North));

				break;
			case SDLK_DOWN:
				p->movingDown = false;

				break;
			}
			break;
		}
	}
}

void PlayState::update(GameStateManager *gsm, double dt) {
	gsm->getActionContainer()->executeAllActions(dt);
	p->move(EnumDirection::West, dt);
}

void PlayState::draw(GameStateManager *gsm) {
	gsm->sdlInitializer->clearScreen();
	p->draw(gsm->sdlInitializer);
	gsm->sdlInitializer->drawScreen();

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
