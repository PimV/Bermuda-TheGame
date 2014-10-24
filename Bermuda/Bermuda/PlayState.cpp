#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include "PauseState.h"
#include <iostream>
#include <algorithm>
#include "Windows.h" 
#include "Inventory.h"
#include "Item.h"

PlayState PlayState::m_PlayState;

//Needed for vector sort
bool drawableSortFunction (DrawableEntity* one,DrawableEntity* two) { return (one->getY() + one->getHeight() < two->getY() + two->getHeight() ); }

PlayState::PlayState(void)
{
}

void PlayState::init(GameStateManager *gsm) {
	this->gsm = gsm;
	mec = new MainEntityContainer();

	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());

	SoundLoader::Instance()->playGameMusic();

	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);
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

		case SDLK_SPACE:
			//TIJDELIJK ROELS INTERACTION UITGESCHAKELT
			//p->interaction = true;
			p->interact();
			break;

		case SDLK_ESCAPE:
			//TODO: methode voor deze escape klik aanmaken?
			this->gsm->pushGameState(PauseState::Instance());
			break;
		case SDLK_i:
			this->p->getInventory()->toggleInventory();
			this->p->getInventory()->printInventory();
			break;
		case SDLK_o: {
			/*	Item* item = new Item(2,16,true,NULL);
			item->setStackSize(5);
			this->p->getInventory()->addItem(item);*/
			this->p->getInventory()->printInventory();
			break;
					 }
		case SDLK_r:
			//this->p->getInventory()->deleteItem(this->p->getInventory()->getItems()[0],5);
			this->p->getInventory()->printInventory();
			break;
		case SDLK_l:
			/*	Item* item = new Item(3,22,true,NULL);
			item->setStackSize(5);
			this->p->getInventory()->addItem(item);*/
			this->p->getInventory()->printInventory();
			break;
		}

		break;

	case SDL_KEYUP:
		switch(mainEvent.key.keysym.sym) {
		case SDLK_LEFT:
			p->StopAnimation();
			p->moveClick = false;
			p->movingLeft = false;
			break;

		case SDLK_RIGHT:
			p->StopAnimation();
			p->moveClick = false;
			p->movingRight = false;
			break;

		case SDLK_UP:
			p->StopAnimation();
			p->moveClick = false;
			p->movingUp = false;
			break;

		case SDLK_DOWN:
			p->StopAnimation();
			p->moveClick = false;
			p->movingDown = false;
			break;

		case SDLK_SPACE:
			p->interaction = false;
			p->StopAnimation();
			break;

		}
		break;
	}
}

void PlayState::update(double dt) {
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);
	/*p->move(dt);*/
	p->update(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}
}

void PlayState::draw() {
	//Calculate begin and end chunks for the camera (+1 and -1 to make it a little bigger then the screen)
	int beginChunkX = floor(camera->getX() / mapLoader->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mapLoader->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mapLoader->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mapLoader->getChunkSize()) + 1;

	std::vector<DrawableEntity*> drawableVector;

	//Loop through all chunks
	for(int i = beginChunkY; i <= endChunkY; i++)
	{
		for(int j = beginChunkX; j <= endChunkX; j++)
		{
			//Background
			std::vector<DrawableEntity*>* vec = this->mec->getBackgroundContainer()->getChunk(i, j);
			if(vec != nullptr)
			{
				for(DrawableEntity* e : *vec)
				{
					e->draw(camera,this->gsm->sdlInitializer->getRenderer());
				}
			}
			//Objecten
			vec = this->mec->getDrawableContainer()->getChunk(i, j);
			if(vec != nullptr)
			{
				for(DrawableEntity* e : *vec)
				{
					drawableVector.push_back(e);
				}
			}

		}
	}

	//Sort drawable object vector
	std::sort(drawableVector.begin(), drawableVector.end(), drawableSortFunction);

	//Draw sorted object vector
	for(DrawableEntity* e : drawableVector)
	{
		e->draw(camera,this->gsm->sdlInitializer->getRenderer());
	}

	if (this->p->getInventory()->isOpen()) {
		this->p->getInventory()->draw();
	}
}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}
