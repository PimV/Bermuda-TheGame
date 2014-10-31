#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include "PauseState.h"
#include <iostream>
#include "Inventory.h"
#include "Item.h"

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

	SoundLoader* soundLoader = gsm->getSoundLoader();
	soundLoader->playGameMusic();

	//this->gameTime = 0;

	std::cout << "Collidable Objects: " << mec->getCollidableContainer()->getContainer().size() << std::endl;

	p = new Player(1, 3, camera, gsm, mec);

	gameTimer = new GameTimer();
	gameTimer->init();
	dayTimer = new DayTimeManager(gameTimer);

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


void PlayState::handleEvents(SDL_Event mainEvent) {
	//p->handleEvents();
	//Process Input

	//Retrieve input
	int x,y;
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
			this->gsm->pushGameState(PauseState::Instance());
			break;
		case SDLK_i:
			this->p->getInventory()->addItem(new Item(2,16,true,NULL));
			this->p->getInventory()->printInventory();
			break;
		case SDLK_o: {
			Item* item = new Item(2,16,true,NULL);
			item->setStackSize(5);
			this->p->getInventory()->addItem(item);
			this->p->getInventory()->printInventory();
			break;
					 }
		case SDLK_r:
			this->p->getInventory()->deleteItem(this->p->getInventory()->getItems()[0],5);
			this->p->getInventory()->printInventory();
			break;
		case SDLK_l:
			Item* item = new Item(3,22,true,NULL);
			item->setStackSize(5);
			this->p->getInventory()->addItem(item);
			this->p->getInventory()->printInventory();
			break;
		//case SDLK_F1:
			//std::cout << this->gsm->lastUpdateLength << std::endl;
			//break;
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

void PlayState::update(double dt) {

	this->updateGameTimers();
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);
	/*p->move(dt);*/
	p->update(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}
}

void PlayState::updateGameTimers() {

	//this->gameTime += this->gsm->lastUpdateLength;
	//std::cout << this->gameTime << std::endl;
	this->gameTimer->updateGameTime(this->gsm->lastUpdateLength);
	this->dayTimer->updateGameTime();
}

long PlayState::getGameTimer() {
	return this->gameTimer->getGameTime();
}

void PlayState::draw() {
	//Clears the screen
	//this->gsm->sdlInitializer->clearScreen();

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
		if (entity->getY() + entity->getHeight() < p->getY() + p->getHeight()) {
			int test = entity->getWidth();
			if (std::find(temp.begin(), temp.end(), entity) != temp.end()) {
				//Remove to temporaryContaienr
				temp.erase(std::find(temp.begin(), temp.end(), entity));
			}
			entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
		} else {
			if (std::find(temp.begin(), temp.end(), entity) == temp.end() && entity != p) {
				//Add to temporaryContainer
				temp.push_back(entity);
			}

		}
	}

	//Load player
	p->draw(camera, gsm->sdlInitializer->getRenderer());

	//Load entities above the player
	for(DrawableEntity* entity : temp)
	{
		entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
	}

}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}
