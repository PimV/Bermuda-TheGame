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
	this->gsm = gsm;
	ready = false;
	showCol = false;
	showInter = false;

	mec = new MainEntityContainer();
	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);

	// TEMPORARY SPAWNPOINT & RABBIT SPAWN 
	Spawnpoint *sp1 = new Spawnpoint(1000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY() + 1000, mapLoader->getChunkSize());
	for (size_t i = 0; i < 1; i++)
	{
		rabbits.push_back(new Rabbit(1001 + i, mapLoader->getChunkSize(), sp1, gsm, mec));
	}

	Spawnpoint *sp2 = new Spawnpoint(2000, mapLoader->getStartPosX() + 1000, mapLoader->getStartPosY(), mapLoader->getChunkSize());
	for (size_t i = 0; i < 1; i++)
	{
		wasps.push_back(new Wasp(2001 + i, mapLoader->getChunkSize(), sp2, gsm, mec));
	}

	//TEMPORARY AXE SPAWN:
	new Axe(9001, p->getX() - 50, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Iron_axe.png", 22, 27)));
	new Pickaxe(9002, p->getX()  + 90, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Iron_pickaxe.png",32, 32)));

	std::cout << "Done" << std::endl;

	//std::thread t(&PlayState::doSomething, this);
	//t.detach();

	SoundLoader::Instance()->playGameMusic();
	ready = true;
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
	if (!ready) {
		return;
	}
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
		case SDLK_F2:
			this->showCol = !this->showCol;
			break;
		case SDLK_F3:
			this->showInter = !this->showInter;
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
			p->setCollisionHeight(10);
			p->setCollisionWidth(24);
			p->setCollisionX(20);
			p->setCollisionY(52);
			break;
		case SDLK_F10:
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
	// check if player died
	if (!ready) {
		return;
	}
	if (p->getHealth() < 1)
	{
		this->gsm->changeGameState(GameOverState::Instance());
	}

	this->updateGameTimers();
	//TODO: Player collision check in de player.move() zelf afhandelen? 
	this->gsm->getActionContainer()->executeAllActions(dt);

	p->update(dt);
	/*if (!p->checkCollision(mec->getCollidableContainer())) {
	p->setPosition();
	}*/

	// TEMPORARY RABBIT UPDATE
	for (Rabbit *rb : this->rabbits)
	{
		rb->update(dt);
		/*if (!rb->checkCollision(mec->getCollidableContainer())) {
		rb->setPosition();
		}*/
	}

	// TEMPORARY WASP UPDATE
	for (Wasp *wa : this->wasps)
	{
		wa->update(dt);
		/*if (!wa->checkCollision(mec->getCollidableContainer())) {
		wa->setPosition();
		}*/
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
	if (!ready) {
		return;
	}
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

					//Draw collision area
					if(this->showCol)
					{
						//TEMP draw collision area
						CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
						if(ce != NULL)
						{
							ce->drawCollidableArea();
						}
					}
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

		//Draw interactable area
		if(this->showInter)
		{
			InteractableEntity* ie = dynamic_cast<InteractableEntity*>(e);
			if(ie != NULL)
			{
				ie->drawInteractableArea();
			}	
		}

		//Draw collision area
		if(this->showCol)
		{
			//TEMP draw collision area
			CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
			if(ce != NULL)
			{
				ce->drawCollidableArea();
			}
		}
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

Player* PlayState::getPlayer()
{
	return this->p;
}

Camera* PlayState::getCamera()
{
	return this->camera;
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
