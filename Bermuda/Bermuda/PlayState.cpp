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


void PlayState::init(GameStateManager *gsm) {
	mec = new MainEntityContainer();
	//Create and load map
	mapLoader = new MapLoader(gsm, mec);	
	mapLoader->loadMap();

	std::cout << "Collidable Objects: " << mec->getCollidableContainer()->getContainer().size() << std::endl;

	//TODO: Window resolution mee geven en correcte X en Y positie. (aan de hand van player location)
	camera = new Camera(0, 0, 1080, 720);

	p = new Player(1, 3, camera);
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

	//if (canMove) {

	p->move(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}
	//bool canMove = true;
	//for(Collidable* c : mec->getCollidableContainer()->getContainer()) {
	//	if (p->intersects(c)) {
	//		p->moveClick = true;
	//		p->resetMovement();
	//		break;
	//	}
	//	//break;

	//}
	//}
}

void PlayState::draw(GameStateManager *gsm) {
	gsm->sdlInitializer->clearScreen();

	//Draw drawable container
	DrawableContainer* drawableContainer = mec->getDrawableContainer();
	for(DrawableEntity* entity : drawableContainer->getContainer())
	{
		entity->draw(camera,gsm->sdlInitializer->getRenderer());
	}

	//Draw player
	p->draw(gsm->sdlInitializer);

	gsm->sdlInitializer->drawScreen();
}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}
