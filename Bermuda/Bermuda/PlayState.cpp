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


	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());

	std::cout << "Collidable Objects: " << mec->getCollidableContainer()->getContainer().size() << std::endl;

	p = new Player(1, 3, camera);
	p->LoadSpriteSheet("Player_Dagger.png", gsm->sdlInitializer->getRenderer());

	temp =  std::vector<DrawableEntity*>();
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

	while(SDL_PollEvent(&mainEvent)) {

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
				//p->resetMovement();
				p->movingLeft = false;
				p->StopAnimation();

				break;
			case SDLK_RIGHT:
				p->moveClick = false;
				//p->resetMovement();
				p->movingRight = false;
				p->StopAnimation();

				break;
			case SDLK_UP:
				p->moveClick = false;
				//p->resetMovement();
				p->movingUp = false;
				p->StopAnimation();

				break;
			case SDLK_DOWN:
				p->moveClick = false;
				//p->resetMovement();
				p->movingDown = false;
				p->StopAnimation();
				break;
			}
			break;
		}
	}
}


void PlayState::update(double dt) {
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);
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

void PlayState::draw() {
	//Clears the screen
	this->gsm->sdlInitializer->clearScreen();

	//Load background
	BackgroundContainer* backgroundContainer = mec->getBackgroundContainer();
	for(DrawableEntity* entity : backgroundContainer->getContainer())
	{
		entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
	}

	//Load drawable container and check order to be drawn
	DrawableContainer* drawableContainer = mec->getDrawableContainer();
	for(DrawableEntity* entity : drawableContainer->getContainer())
	{
		if (entity->getY() < p->getY() - p->getHeight()) {
			if (std::find(temp.begin(), temp.end(), entity) != temp.end()) {
				//Remove to temporaryContaienr
				temp.erase(std::find(temp.begin(), temp.end(), entity));
			}
			entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
		} else {
			if (std::find(temp.begin(), temp.end(), entity) == temp.end()) {
				//Add to temporaryContainer
				temp.push_back(entity);
			}

		}
	}

	//Load player
	p->draw(this->gsm->sdlInitializer);

	//Load entities above the player
	for(DrawableEntity* entity : temp)
	{
		entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
	}

	//Draw screen
	this->gsm->sdlInitializer->drawScreen();
}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}