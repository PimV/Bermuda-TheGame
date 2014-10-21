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

	SoundLoader* soundLoader = gsm->getSoundLoader();
	soundLoader->playGameMusic();

	p = new Player(1, mapLoader->getChunkSize(), 3, camera, gsm, mec);

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
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);
	/*p->move(dt);*/
	p->update(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}
}

void PlayState::draw() {

	int beginChunkX = floor(camera->getX() / mapLoader->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mapLoader->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mapLoader->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mapLoader->getChunkSize()) + 1;

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
			std::vector<DrawableEntity*>* vec = this->mec->getDrawableContainer()->getChunk(i, j);
			if(vec != nullptr)
			{
				for(DrawableEntity* e : *vec)
				{
					e->draw(camera,this->gsm->sdlInitializer->getRenderer());
				}
			}

		}
	}



	//DrawableContainer* drawableContainer = mec->getDrawableContainer();
	//for(DrawableEntity* entity : drawableContainer->getContainer())
	//{
	//	if (entity->getY() + entity->getHeight() < p->getY() + p->getHeight()) {
	//		int test = entity->getWidth();
	//		if (std::find(temp.begin(), temp.end(), entity) != temp.end()) {
	//			//Remove to temporaryContaienr
	//			temp.erase(std::find(temp.begin(), temp.end(), entity));
	//		}
	//		entity->draw(camera,this->gsm->sdlInitializer->getRenderer());
	//	} else {
	//		if (std::find(temp.begin(), temp.end(), entity) == temp.end() && entity != p) {
	//			//Add to temporaryContainer
	//			temp.push_back(entity);
	//		}

	//	}
	//}

	std::vector<DrawableEntity*>* contt =  this->mec->getDrawableContainer()->getChunk(floor(p->getY() / 300), floor(p->getX() / 300));
	for(DrawableEntity* e : *contt)
	{
		e->draw(camera,this->gsm->sdlInitializer->getRenderer());
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
