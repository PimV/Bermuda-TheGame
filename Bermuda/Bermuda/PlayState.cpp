#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include "PauseState.h"
#include "LoadingState.h"
#include "GameOverState.h"
#include <iostream>
#include <algorithm>
#include "Windows.h" 
#include "Inventory.h"
#include "Item.h"
#include <thread>
#include "ToolAxe.h"
#include "ItemCarrot.h"

//TEMPORARY AXE SPAWN:
#include "Axe.h"
#include "Pickaxe.h"

PlayState PlayState::m_PlayState;

//Needed for vector sort
bool drawableSortFunction(DrawableEntity* one, DrawableEntity* two) { return (one->getY() + one->getHeight() < two->getY() + two->getHeight()); }

PlayState::PlayState(void)
{
}

void PlayState::init(GameStateManager *gsm) {
	this->mapLoaded = false;
	this->gsm = gsm;

	this->gsm->pushGameState(LoadingState::Instance());

	mec = new MainEntityContainer();
	mapLoader = new MapLoader(this->gsm, mec);
	std::thread t(&PlayState::doSomething, this);
	t.detach();

	SoundLoader::Instance()->playGameMusic();
}

//MainEntityContainer* PlayState::getMainEntityContainer()
//{
//	return this->mec;
//}

void PlayState::doSomething()
{
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);

	SoundLoader* soundLoader = gsm->getSoundLoader();
	soundLoader->playGameMusic();

	temp =  std::vector<DrawableEntity*>();

	//TEMPORARY AXE SPAWN:
	new Axe(9001, p->getX() - 50, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Axe.png", 48, 48)));
	new Pickaxe(9002, p->getX()  + 90, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Pickaxe.png", 48, 48)));
	
	this->gsm->popState();
	this->mapLoaded = true;
}

void PlayState::cleanup() {

}

void PlayState::pause() {
	if (this->p != nullptr)
	{
	this->p->moveClick = true;
	this->p->resetMovement();
}
}

void PlayState::resume() {

}


void PlayState::handleEvents(SDL_Event mainEvent) {
	//p->handleEvents();
	//Process Input

	//Retrieve input
	switch (mainEvent.type) {
	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {
			p->destX = x + this->camera->getX();
			p->destY = y + this->camera->getY();
			p->resetMovement();
			p->moveClick = true;
		}
		break;

	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym) {
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
		case SDLK_LSHIFT:
			p->sprinting = true;
			break;
		case SDLK_F1:
			//Print player location
			std::cout << "Current Location of player: " << p->getX() << ":" << p->getY() << std::endl;
			break;
		case SDLK_F5: 
			{
			//Consume Carrot (Same method as 9)
			Item* i = p->getInventory()->getItemById(1, true);
			if (i != nullptr) {
				std::cout << "Item found!" << std::endl;
				if (i->isConsumable()) {
					Consumable* c = (Consumable*)i;
					c->consume(p);
				} else if (i->isEquipable()) {
					Equipable* e = (Equipable*)i;
					e->equip(p);
				}
			}
			break;
					 }
		case SDLK_F6: 
			{
			//Equip Axe (Same method as 0)
			Item* i = p->getInventory()->getItemById(3, true);
			if (i != nullptr) {
				std::cout << "Item found!" << std::endl;
				if (i->isConsumable()) {
					Consumable* c = (Consumable*)i;
					c->consume(p);
				} else if (i->isEquipable()) {
					Equipable* e = (Equipable*)i;
					e->equip(p);
				}
			}
			break;
					 }
		case SDLK_F11:
			//Enable collision
			p->setCollisionHeight(p->getHeight() - 15);
			p->setCollisionWidth(p->getWidth()/4);
			p->setCollisionX((p->getWidth() - p->getCollisionWidth()) / 2);
			p->setCollisionY(0);
			break;
		case SDLK_F12:
			//Disable collision
		case SDLK_p:
			p->setCollisionHeight(0);
			p->setCollisionWidth(0);
			p->setCollisionX(-10000);
			p->setCollisionY(-10000);
			break;
		case SDLK_SPACE:
			//TIJDELIJK ROELS INTERACTION UITGESCHAKELT
			p->interaction = true;
			p->interact();
			break;
		case SDLK_0: {
			//Consume Carrot (Same method as 9)
			Item* i = p->getInventory()->getItemById(1, true);
			if (i != nullptr) {
				std::cout << "Item found!" << std::endl;
				if (i->isConsumable()) {
					Consumable* c = (Consumable*)i;
					c->consume(p);
				} else if (i->isEquipable()) {
					Equipable* e = (Equipable*)i;
					e->equip(p);
				}
			}
			break;
					 }
		case SDLK_9: {
			//Equip Axe (Same method as 0)
			Item* i = p->getInventory()->getItemById(3, true);
			if (i != nullptr) {
				std::cout << "Item found!" << std::endl;
				if (i->isConsumable()) {
					Consumable* c = (Consumable*)i;
					c->consume(p);
				} else if (i->isEquipable()) {
					Equipable* e = (Equipable*)i;
					e->equip(p);
				}
			}
			break;
					 }

		case SDLK_ESCAPE:
			//TODO: methode voor deze escape klik aanmaken?
			this->gsm->pushGameState(PauseState::Instance());
			break;
		case SDLK_i:
			this->p->getInventory()->toggleInventory();
			this->p->getInventory()->printInventory();
			break;

		case SDLK_g:
			this->gsm->changeGameState(GameOverState::Instance());
			break;
		}

		break;

	case SDL_KEYUP:
		switch (mainEvent.key.keysym.sym) {
		case SDLK_LEFT:
			p->StopAnimation();
			p->moveClick = false;
			p->movingLeft = false;
			break;
		case SDLK_q:
			p->setCollisionHeight(p->getHeight() - 15);
			p->setCollisionWidth(p->getWidth()/4);
			p->setCollisionX((p->getWidth() - p->getCollisionWidth()) / 2);
			p->setCollisionY(0);
			break;
		case SDLK_LSHIFT:
			p->sprinting = false;
			//p->moveSpeed = p->maxSpeed;
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
	// check if player died
	if (p->getHealth() < 1) {
		this->gsm->changeGameState(GameOverState::Instance());
	}

	this->updateGameTimers();
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);

	p->update(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}
	
	//Update all respawnable entities
	for (size_t i = 0; i < mec->getRespawnContainer()->getContainer()->size(); i++) {
		mec->getRespawnContainer()->getContainer()->at(i)->update(dt);
	}
}

void PlayState::updateGameTimers() {

	GameTimer::Instance()->updateGameTime(GameStateManager::Instance()->getUpdateLength());
	//DayTimeTimer::Instance()->updateDayTime();
	GameTimer::Instance()->updateDayTime();
}

long PlayState::getGameTimer() {
	return GameTimer::Instance()->getGameTime();
}

void PlayState::draw() 
{
	if (this->mapLoaded)
	{
		//Calculate begin and end chunks for the camera (+1 and -1 to make it a little bigger then the screen)
		int beginChunkX = floor(camera->getX() / mapLoader->getChunkSize()) - 1;
		int endChunkX = floor((camera->getX() + camera->getWidth()) / mapLoader->getChunkSize()) + 1;
		int beginChunkY = floor(camera->getY() / mapLoader->getChunkSize()) - 1;
		int endChunkY = floor((camera->getY() + camera->getHeight()) / mapLoader->getChunkSize()) + 1;

		std::vector<DrawableEntity*> drawableVector;

		//Loop through all chunks
		for (int i = beginChunkY; i <= endChunkY; i++)
		{
			for (int j = beginChunkX; j <= endChunkX; j++)
			{
				//Background
				std::vector<DrawableEntity*>* vec = this->mec->getBackgroundContainer()->getChunk(i, j);
				if (vec != nullptr)
				{
					for (DrawableEntity* e : *vec)
					{
						e->draw(camera, this->gsm->sdlInitializer->getRenderer());
					}
				}
				//Objecten
				vec = this->mec->getDrawableContainer()->getChunk(i, j);
				if (vec != nullptr)
				{
					for (DrawableEntity* e : *vec)
					{
						drawableVector.push_back(e);
					}
				}

			}
		}

		//Sort drawable object vector
		std::sort(drawableVector.begin(), drawableVector.end(), drawableSortFunction);

		//Draw sorted object vector
		for (DrawableEntity* e : drawableVector)
		{
			e->draw(camera, this->gsm->sdlInitializer->getRenderer());
		}

		if (this->p->getInventory()->isOpen()) {
			this->p->getInventory()->draw();
		}

		// Draw the player status
		this->gsm->sdlInitializer->drawText(std::string("Health: " + to_string(p->getHealth())), 1150, 5, 100, 25);
		this->gsm->sdlInitializer->drawText(std::string("Hunger: " + to_string(p->getHunger())), 1150, 35, 100, 25);
		//this->gsm->sdlInitializer->drawText(std::string("Thirst: " + to_string(p->getThirst())), 1150, 65, 100, 25);
		// if current hour is smaller then 9 
		if (GameTimer::Instance()->getCurrentDayPart() > 9)
			this->gsm->sdlInitializer->drawText(std::string("  Hour: " + to_string(GameTimer::Instance()->getCurrentDayPart())), 1150, 95, 90, 25);
		else
			this->gsm->sdlInitializer->drawText(std::string("  Hour: 0" + to_string(GameTimer::Instance()->getCurrentDayPart())), 1150, 95, 90, 25);
	}
}

//ERROR Deze methode word nooit aangeroepen volgens mij.
//Betekend dus dat de playstate nooit verwijderd wordt
PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
	std::cout << "deleting playstate" << endl; 
}
