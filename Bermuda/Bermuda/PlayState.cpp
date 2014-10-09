#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include "PauseState.h"
#include <iostream>

PlayState PlayState::m_PlayState;

PlayState::PlayState(void)
{
}


void PlayState::init(GameStateManager *gsm) {
	this->gsm = gsm;
	mec = new MainEntityContainer();
<<<<<<< HEAD

	mapLoader = new MapLoader(this->gsm, mec);
=======
	mapLoader = new MapLoader(gsm, mec);
>>>>>>> parent of 29448c2... First Collision implementation
	mapLoader->loadMap();
	
	//TODO: Window resolution mee geven en correcte X en Y positie. (aan de hand van player location)
	camera = new Camera(0, 0, 1600, 900);

	p = new Player(1, 3, camera);
}

void PlayState::cleanup() {

}

void PlayState::pause() {
	this->p->moveClick = true;
	this->p->resetMovement();
}

void PlayState::resume() {

}


void PlayState::handleEvents() {
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
				//std::cout << x << "  " << y << std::endl;
				p->destX = x + this->camera->getX();
				p->destY = y + this->camera->getY();
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
			case SDLK_ESCAPE:
				//TODO: methode voor deze escape klik aanmaken?
				this->gsm->pushGameState(new PauseState());
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

<<<<<<< HEAD

void PlayState::update(double dt) {
	this->gsm->getActionContainer()->executeAllActions(dt);
=======
void PlayState::update(GameStateManager *gsm, double dt) {
	gsm->getActionContainer()->executeAllActions(dt);
>>>>>>> parent of 29448c2... First Collision implementation
	p->move(dt);
}

<<<<<<< HEAD
void PlayState::draw() {
	this->gsm->sdlInitializer->clearScreen();
=======
void PlayState::draw(GameStateManager *gsm) {
	gsm->sdlInitializer->clearScreen();
>>>>>>> parent of 29448c2... First Collision implementation
	
	//Draw drawable container
	DrawableContainer* drawableContainer = mec->getDrawableContainer();
	//std::vector<DrawableEntity*>* drawVec = mec->getDrawableContainer();
	//for(DrawableEntity* entity : *drawVec)
	for(DrawableEntity* entity : drawableContainer->getContainer())
	{
		entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
	}
	
	//Draw player
	p->draw(this->gsm->sdlInitializer);

	this->gsm->sdlInitializer->drawScreen();
}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}
