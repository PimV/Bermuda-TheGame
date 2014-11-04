#include "PlayState.h"
#include "MenuState.h"
#include "Button.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "ClickAction.h"
#include "MoveAction.h"
#include "PauseState.h"
#include "LoadingState.h"
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
	this->gsm = gsm;

	//this->gsm->pushGameState(LoadingState::Instance());

	mec = new MainEntityContainer();
	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);

	// TEMPORARY SPAWNPOINT & RABBIT SPAWN 
	Spawnpoint *sp1 = new Spawnpoint(1000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY() + 1000, mapLoader->getChunkSize());
	for (size_t i = 0; i < 20; i++)
	{
		rabbits.push_back(new Rabbit(1001, mapLoader->getChunkSize(), sp1, gsm, mec));
	}

	Spawnpoint *sp2 = new Spawnpoint(2000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY(), mapLoader->getChunkSize());
	for (size_t i = 0; i < 20; i++)
	{
		wasps.push_back(new Wasp(2001, mapLoader->getChunkSize(), sp2, gsm, mec));
	}

	//TEMPORARY AXE SPAWN:
	new Axe(9001, p->getX() - 50, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Axe.png", 48, 48)));
	new Pickaxe(9002, p->getX()  + 90, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Pickaxe.png", 48, 48)));
	

	//std::thread t(&PlayState::doSomething, this);
	//t.detach();
	
	SoundLoader::Instance()->playGameMusic();
}

MainEntityContainer* PlayState::getMainEntityContainer()
{
	return this->mec;
}

void PlayState::doSomething()
{
	//mapLoader->loadMap();
	//camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	//p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);

	//// TEMPORARY SPAWNPOINT & RABBIT SPAWN 
	//Spawnpoint *sp1 = new Spawnpoint(1000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY() + 1000, mapLoader->getChunkSize());
	//for (size_t i = 0; i < 20; i++)
	//{
	//	rabbits.push_back(new Rabbit(1001 + i, mapLoader->getChunkSize(), sp1, gsm, mec));
	//}

	//Spawnpoint *sp2 = new Spawnpoint(2000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY(), mapLoader->getChunkSize());
	//for (size_t i = 0; i < 20; i++)
	//{
	//	wasps.push_back(new Wasp(2001 + i, mapLoader->getChunkSize(), sp2, gsm, mec));
	//}

	////TEMPORARY AXE SPAWN:
	//new Axe(9001, p->getX() - 50, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Axe.png", 48, 48)));
	//new Pickaxe(9002, p->getX()  + 90, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Pickaxe.png", 48, 48)));
	//
	//this->gsm->popState();
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
	int x, y;
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
			//Arrow left key
			p->resetMovement();
			p->moveClick = false;
			p->movingLeft = true;
			p->movingRight = false;
			break;
		case SDLK_RIGHT:
			//Arrow right key
			p->resetMovement();
			p->moveClick = false;
			p->movingRight = true;
			p->movingLeft = false;
			break;
		case SDLK_UP:
			//Arrow up key
			p->resetMovement();
			p->moveClick = false;
			p->movingUp = true;
			p->movingDown = false;
			break;
		case SDLK_DOWN:
			//Arrow down key
			p->resetMovement();
			p->moveClick = false;
			p->movingDown = true;
			p->movingUp = false;
			break;
		case SDLK_LSHIFT:
			//Sprint
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
			p->setCollisionHeight(0);
			p->setCollisionWidth(0);
			p->setCollisionX(-10000);
			p->setCollisionY(-10000);
			break;
		case SDLK_SPACE:
			//Current interact button (= space)
			//TIJDELIJK ROELS INTERACTION UITGESCHAKELT
			p->interaction = true;
			p->interact();
			break;


		case SDLK_ESCAPE:
			//Go to pause state on 'Escape'
			//TODO: methode voor deze escape klik aanmaken?
			this->gsm->pushGameState(PauseState::Instance());
			break;
		case SDLK_i:
			//Open inventory
			this->p->getInventory()->toggleInventory();
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
		case SDLK_LSHIFT:
			p->sprinting = false;
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

	p->update(dt);
	if (!p->checkCollision(mec->getCollidableContainer())) {
		p->setPosition();
	}

	// TEMPORARY RABBIT UPDATE
	for (Rabbit *rb : this->rabbits)
	{
		rb->update(dt);
		if (!rb->checkCollision(mec->getCollidableContainer())) {
			rb->setPosition();
		}
	}

	// TEMPORARY WASP UPDATE
	for (Wasp *wa : this->wasps)
	{
		wa->update(dt);
		if (!wa->checkCollision(mec->getCollidableContainer())) {
			wa->setPosition();
		}
	}

	//Update all respawnable entities
	for (size_t i = 0; i < mec->getRespawnContainer()->getContainer()->size(); i++) {
		mec->getRespawnContainer()->getContainer()->at(i)->update(dt);
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
}

PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
}
